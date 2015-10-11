#include <iostream>
#include <assert.h>
#include <stdio.h>

#include "Hashtable.hh"
#include "MassTrans.hh"
#include "Transaction.hh"
#include "simple_str.hh"

#define DS 0
#define USE_STRINGS 1

#if DS == 0
#if USE_STRINGS == 1
typedef Hashtable<std::string, simple_str, false, 1000000> ds;
#else
typedef Hashtable<int, simple_str, false, 1000000> ds;
#endif
#else
typedef MassTrans<std::string> ds;
#endif

#define NTRANS 5000000
#define NINIT 100000
#define MAX_VALUE NINIT
using namespace std;

std::string value;

struct Rand {
    typedef uint32_t result_type;
    
    result_type u, v;
    Rand(result_type u, result_type v) : u(u|1), v(v|1) {}
    
    inline result_type operator()() {
        v = 36969*(v & 65535) + (v >> 16);
        u = 18000*(u & 65535) + (u >> 16);
        return (v << 16) + u;
    }
    
    static constexpr result_type max() {
        return (uint32_t)-1;
    }
    
    static constexpr result_type min() {
        return 0;
    }
};


void run(ds& h) {
    std::uniform_int_distribution<long> slotdist(0, MAX_VALUE);
    for (int i = 0; i < NTRANS; ++i) {
        auto transseed = i;
        uint32_t seed = transseed*3;// + (uint32_t)me*NTRANS*7 + (uint32_t)GLOBAL_SEED*MAX_THREADS*NTRANS*11;
        auto seedlow = seed & 0xffff;
        auto seedhigh = seed >> 16;
        Rand transgen(seed, seedlow << 16 | seedhigh);
            
        int key = slotdist(transgen);
        std::string value;
#if DS == 0
        //TRANSACTION{
#if USE_STRINGS == 1
            std::string s = std::to_string(key);
            h.read(s, value);
#else
	    std::string s = std::to_string(key);
	    h.read(key, value);
#endif
        //} RETRY(false);
#else
        TRANSACTION{
#if USE_STRINGS == 1
            std::string s = std::to_string(key);
            h.transGet(s, value);
#else
            h.transGet(key, value);
#endif 
	} RETRY(false);
#endif
    }
    
}


void init(ds& h) {
    for (int i = 0; i < NINIT; ++i) {
        TRANSACTION{
#if USE_STRINGS == 1
            std::string s = std::to_string(i);
            h.put(s, value);
#else
	    h.put(i, value);
#endif
        } RETRY(false);
    }
    
}


void print_time(struct timeval tv1, struct timeval tv2) {
    printf("%f\n", (tv2.tv_sec-tv1.tv_sec) + (tv2.tv_usec-tv1.tv_usec)/1000000.0);
}

int main() {
    value = std::string('a', 100);
    ds h;
#if DS != 0
    h.thread_init();
#endif
    
    init(h);
    ct = 0;    
    struct timeval tv1,tv2;
    gettimeofday(&tv1, NULL);
    
    run(h);
    
    gettimeofday(&tv2, NULL);
    printf("Time taken: ");
    print_time(tv1, tv2);
    
    std::cout << "traversal: " << ct  << std::endl;
    std::cout << "Max traversal: " << max_ct << std::endl;
}