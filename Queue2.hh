#pragma once

#include <list>
#include "TaggedLow.hh"
#include "Transaction.hh"
#include "TWrapped.hh"

/*
 * This queue uses pessimistic locking (similar to the scheme proposed in the TDSL paper
 * http://dl.acm.org/citation.cfm?doid=2908080.2908112).
 * 
 * Any modification or read of the head of the list (pop/front) locks the queue for the remainder
 * of the txn. This means that aborts only occur upon encountering empty queues.
 */


template <typename T, bool Opacity = true, unsigned BUF_SIZE = 1000000>
class Queue2: public Shared {
public:
    typedef typename std::conditional<Opacity, TVersion, TNonopaqueVersion>::type version_type;
    typedef T value_type;

    Queue2() : head_(0), tail_(0), queueversion_(0) {}

    static constexpr TransItem::flags_type delete_bit = TransItem::user0_bit;
    static constexpr TransItem::flags_type read_writes = TransItem::user0_bit<<1;
    static constexpr TransItem::flags_type list_bit = TransItem::user0_bit<<2;
    static constexpr TransItem::flags_type empty_bit = TransItem::user0_bit<<3;
    static constexpr TransItem::flags_type push_bit = TransItem::user0_bit<<4;
    static constexpr int pushitem_key = -1;

    // NONTRANSACTIONAL PUSH/POP/EMPTY
    void nontrans_push(T v) {
        queueSlots[tail_] = v;
        tail_ = (tail_+1)%BUF_SIZE;
        assert(head_ != tail_);
    }
    
    T nontrans_pop() {
        assert(head_ != tail_);
        T v = queueSlots[head_];
        head_ = (head_+1)%BUF_SIZE;
        return v;
    }

    bool nontrans_empty() const {
        return head_ == tail_;
    }

    template <typename RandomGen>
    void nontrans_shuffle(RandomGen gen) {
        auto head = &queueSlots[head_];
        auto tail = &queueSlots[tail_];
        // don't support wrap-around shuffle
        assert(head < tail);
        std::shuffle(head, tail, gen);
    }

    void nontrans_clear() {
        while (!nontrans_empty())
            nontrans_pop();
    }
    void push(const T& v) {
        auto item = Sto::item(this, pushitem_key);
        if (item.has_write()) {
            if (!is_list(item)) {
                auto& val = item.template write_value<T>();
                std::list<T> write_list;
                if (!is_empty(item)) {
                    write_list.push_back(val);
                    item.clear_flags(empty_bit);
                }
                write_list.push_back(v);
                item.clear_write();
                item.add_write(write_list);
                item.add_flags(list_bit | push_bit);
            }
            else {
                auto& write_list = item.template write_value<std::list<T>>();
                write_list.push_back(v);
            }
        }
        else {
            item.add_write(v);
        }
    }

    bool pop() {
        auto tailitem = Sto::item(this,pushitem_key);
        // lock the queue until done with txn
        if (!queueversion_.is_locked_here()) {
            if (!queueversion_.try_lock()) { 
                Sto::abort(); 
            }
        }

        fence();
        auto index = head_;
        auto item = Sto::item(this, index);
        
        while (1) {
           if (index == tail_) {
               // we need to make sure that we unlock, since no other item will have
               // been written to if the queue is empty
               if (!tailitem.has_write()) tailitem.add_write(0);

               fence();
                // empty queue
                if (index == tail_) {
                    if (tailitem.has_write()) {
                        if (is_list(tailitem) && has_push(tailitem)) {
                            auto& write_list = tailitem.template write_value<std::list<T>>();
                            // if there is an element to be pushed on the queue, return addr of queue element
                            if (!write_list.empty()) {
                                write_list.pop_front();
                                item.add_flags(read_writes);
                                return true;
                            }
                            else return false;
                        }
                        // not a list, has exactly one element
                        else if (!is_empty(tailitem)) {
                            tailitem.add_flags(empty_bit);
                            return true;
                        }
                        else return false;
                    }
                    // fail if trying to read from an empty queue
                    else {
                        return false;  
                    }
                } 
            }
            if (has_delete(item)) {
                index = (index + 1) % BUF_SIZE;
                item = Sto::item(this, index);
            }
            else break;
        }
        item.add_flags(delete_bit);
        item.add_write(0);
        return true;
    }

    bool front(T& val) {
        auto tailitem = Sto::item(this,pushitem_key);
        // lock the queue until done with txn
        if (!queueversion_.is_locked_here()) {
            if (!queueversion_.try_lock()) { 
                Sto::abort(); 
            }
        }

        fence();
        unsigned index = head_;
        auto item = Sto::item(this, index);
        while (1) {
            // empty queue, so we have to add a read of the queueversion
            if (index == tail_) {
                // we need to make sure that we unlock, since no other item will have
                // been written to if the queue is empty
                if (!tailitem.has_write()) tailitem.add_write(0);

                fence();
                if (index == tail_) {
                    if (tailitem.has_write() && has_push(tailitem)) {
                        if (is_list(tailitem)) {
                            auto& write_list= tailitem.template write_value<std::list<T>>();
                            // if there is an element to be pushed on the queue, return addr of queue element
                            if (!write_list.empty()) {
                                val = write_list.front();
                                return true;
                            }
                            else return false;
                        }
                        // not a list, has exactly one element
                        else if (!is_empty(tailitem) && has_push(tailitem)) {
                            auto& v = tailitem.template write_value<T>();
                            val = v;
                            return true;
                        }
                        else return false;
                    }
                    return false;
                }
            }
            if (has_delete(item)) {
                index = (index + 1) % BUF_SIZE;
                item = Sto::item(this, index);
            }
            else break;
        }
        val = queueSlots[index];
        return true;
    }

private:
    bool has_push(const TransItem& item) {
        return item.flags() & push_bit;
    }

    bool has_delete(const TransItem& item) {
        return item.flags() & delete_bit;
    }
    
    bool is_rw(const TransItem& item) {
        return item.flags() & read_writes;
    }
 
    bool is_list(const TransItem& item) {
        return item.flags() & list_bit;
    }
 
    bool is_empty(const TransItem& item) {
        return item.flags() & empty_bit;
    }

    bool lock(TransItem& item, Transaction& txn) override {
        if ((item.key<int>() == pushitem_key) && !queueversion_.is_locked_here())  {
            return txn.try_lock(item, queueversion_);
        }
        return true;
    }

    bool check(TransItem&, Transaction&) override {
        // we should actually never call this function because we always lock when we observe some
        // state of the queue (during a pop/front!) This means that no one could push/pop
        // from the queue after we called pop/front.`
        // THIS IS WRONG: check if we read off the write_list. We should only abort if both: 
        //      1) we saw the queue was empty during a pop/front and read off our own write list AND
        //      2) someone else has pushed onto the queue before we got here
        assert(0);
        return false;
    }

    void install(TransItem& item, Transaction& txn) override {
        (void)txn;
        // queueversion_ should be locked here because we must have popped
        // or locked to push onto the queue
        assert(queueversion_.is_locked_here());
        // install pops
        if (has_delete(item)) {
            // only increment head if item popped from actual q
            if (!is_rw(item)) {
                head_ = (head_+1) % BUF_SIZE;
            }
        }
        // install pushes, but only if we added a write to
        //  the push/tail item on a push
        else if (item.key<int>() == pushitem_key) {
            auto head_index = head_;
            // write all the elements
            if (is_list(item) && has_push(item)) {
                auto& write_list = item.template write_value<std::list<T>>();
                while (!write_list.empty()) {
                    // assert queue is not out of space            
                    assert(tail_ != (head_index-1) % BUF_SIZE);
                    queueSlots[tail_] = write_list.front();
                    write_list.pop_front();
                    tail_ = (tail_+1) % BUF_SIZE;
                }
            }
            else if (!is_empty(item)) {
                auto& val = item.template write_value<T>();
                queueSlots[tail_] = val;
                tail_ = (tail_+1) % BUF_SIZE;
            }
        }
    }
    
    void unlock(TransItem& item) override {
        (void)item;
        if (queueversion_.is_locked_here()) {
            queueversion_.unlock();
        }
    }

    void cleanup(TransItem& item, bool committed) override {
        (void)item;
        (void)committed;
        if (queueversion_.is_locked_here()) {
            queueversion_.unlock();
        }
    }

    T queueSlots[BUF_SIZE];

    unsigned head_;
    unsigned tail_;
    version_type queueversion_;
};
