/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef DistributedSTO_H
#define DistributedSTO_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "DistributedSTO_types.h"



#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class DistributedSTOIf {
 public:
  virtual ~DistributedSTOIf() {}
  virtual void read(std::string& _return, const int64_t objid) = 0;
  virtual bool lock(const int64_t tuid, const std::vector<int64_t> & objids) = 0;
  virtual bool check(const int64_t tuid, const std::map<int64_t, int64_t> & objid_ver_pairs) = 0;
  virtual void install(const int64_t tuid, const int64_t tid, const std::map<int64_t, std::string> & objid_data_pairs) = 0;
  virtual void abort(const int64_t tuid) = 0;
};

class DistributedSTOIfFactory {
 public:
  typedef DistributedSTOIf Handler;

  virtual ~DistributedSTOIfFactory() {}

  virtual DistributedSTOIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(DistributedSTOIf* /* handler */) = 0;
};

class DistributedSTOIfSingletonFactory : virtual public DistributedSTOIfFactory {
 public:
  DistributedSTOIfSingletonFactory(const boost::shared_ptr<DistributedSTOIf>& iface) : iface_(iface) {}
  virtual ~DistributedSTOIfSingletonFactory() {}

  virtual DistributedSTOIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(DistributedSTOIf* /* handler */) {}

 protected:
  boost::shared_ptr<DistributedSTOIf> iface_;
};

class DistributedSTONull : virtual public DistributedSTOIf {
 public:
  virtual ~DistributedSTONull() {}
  void read(std::string& /* _return */, const int64_t /* objid */) {
    return;
  }
  bool lock(const int64_t /* tuid */, const std::vector<int64_t> & /* objids */) {
    bool _return = false;
    return _return;
  }
  bool check(const int64_t /* tuid */, const std::map<int64_t, int64_t> & /* objid_ver_pairs */) {
    bool _return = false;
    return _return;
  }
  void install(const int64_t /* tuid */, const int64_t /* tid */, const std::map<int64_t, std::string> & /* objid_data_pairs */) {
    return;
  }
  void abort(const int64_t /* tuid */) {
    return;
  }
};

typedef struct _DistributedSTO_read_args__isset {
  _DistributedSTO_read_args__isset() : objid(false) {}
  bool objid :1;
} _DistributedSTO_read_args__isset;

class DistributedSTO_read_args {
 public:

  DistributedSTO_read_args(const DistributedSTO_read_args&);
  DistributedSTO_read_args& operator=(const DistributedSTO_read_args&);
  DistributedSTO_read_args() : objid(0) {
  }

  virtual ~DistributedSTO_read_args() throw();
  int64_t objid;

  _DistributedSTO_read_args__isset __isset;

  void __set_objid(const int64_t val);

  bool operator == (const DistributedSTO_read_args & rhs) const
  {
    if (!(objid == rhs.objid))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_read_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_read_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_read_pargs {
 public:


  virtual ~DistributedSTO_read_pargs() throw();
  const int64_t* objid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DistributedSTO_read_result__isset {
  _DistributedSTO_read_result__isset() : success(false) {}
  bool success :1;
} _DistributedSTO_read_result__isset;

class DistributedSTO_read_result {
 public:

  DistributedSTO_read_result(const DistributedSTO_read_result&);
  DistributedSTO_read_result& operator=(const DistributedSTO_read_result&);
  DistributedSTO_read_result() : success() {
  }

  virtual ~DistributedSTO_read_result() throw();
  std::string success;

  _DistributedSTO_read_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const DistributedSTO_read_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_read_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_read_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DistributedSTO_read_presult__isset {
  _DistributedSTO_read_presult__isset() : success(false) {}
  bool success :1;
} _DistributedSTO_read_presult__isset;

class DistributedSTO_read_presult {
 public:


  virtual ~DistributedSTO_read_presult() throw();
  std::string* success;

  _DistributedSTO_read_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DistributedSTO_lock_args__isset {
  _DistributedSTO_lock_args__isset() : tuid(false), objids(false) {}
  bool tuid :1;
  bool objids :1;
} _DistributedSTO_lock_args__isset;

class DistributedSTO_lock_args {
 public:

  DistributedSTO_lock_args(const DistributedSTO_lock_args&);
  DistributedSTO_lock_args& operator=(const DistributedSTO_lock_args&);
  DistributedSTO_lock_args() : tuid(0) {
  }

  virtual ~DistributedSTO_lock_args() throw();
  int64_t tuid;
  std::vector<int64_t>  objids;

  _DistributedSTO_lock_args__isset __isset;

  void __set_tuid(const int64_t val);

  void __set_objids(const std::vector<int64_t> & val);

  bool operator == (const DistributedSTO_lock_args & rhs) const
  {
    if (!(tuid == rhs.tuid))
      return false;
    if (!(objids == rhs.objids))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_lock_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_lock_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_lock_pargs {
 public:


  virtual ~DistributedSTO_lock_pargs() throw();
  const int64_t* tuid;
  const std::vector<int64_t> * objids;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DistributedSTO_lock_result__isset {
  _DistributedSTO_lock_result__isset() : success(false) {}
  bool success :1;
} _DistributedSTO_lock_result__isset;

class DistributedSTO_lock_result {
 public:

  DistributedSTO_lock_result(const DistributedSTO_lock_result&);
  DistributedSTO_lock_result& operator=(const DistributedSTO_lock_result&);
  DistributedSTO_lock_result() : success(0) {
  }

  virtual ~DistributedSTO_lock_result() throw();
  bool success;

  _DistributedSTO_lock_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const DistributedSTO_lock_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_lock_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_lock_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DistributedSTO_lock_presult__isset {
  _DistributedSTO_lock_presult__isset() : success(false) {}
  bool success :1;
} _DistributedSTO_lock_presult__isset;

class DistributedSTO_lock_presult {
 public:


  virtual ~DistributedSTO_lock_presult() throw();
  bool* success;

  _DistributedSTO_lock_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DistributedSTO_check_args__isset {
  _DistributedSTO_check_args__isset() : tuid(false), objid_ver_pairs(false) {}
  bool tuid :1;
  bool objid_ver_pairs :1;
} _DistributedSTO_check_args__isset;

class DistributedSTO_check_args {
 public:

  DistributedSTO_check_args(const DistributedSTO_check_args&);
  DistributedSTO_check_args& operator=(const DistributedSTO_check_args&);
  DistributedSTO_check_args() : tuid(0) {
  }

  virtual ~DistributedSTO_check_args() throw();
  int64_t tuid;
  std::map<int64_t, int64_t>  objid_ver_pairs;

  _DistributedSTO_check_args__isset __isset;

  void __set_tuid(const int64_t val);

  void __set_objid_ver_pairs(const std::map<int64_t, int64_t> & val);

  bool operator == (const DistributedSTO_check_args & rhs) const
  {
    if (!(tuid == rhs.tuid))
      return false;
    if (!(objid_ver_pairs == rhs.objid_ver_pairs))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_check_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_check_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_check_pargs {
 public:


  virtual ~DistributedSTO_check_pargs() throw();
  const int64_t* tuid;
  const std::map<int64_t, int64_t> * objid_ver_pairs;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DistributedSTO_check_result__isset {
  _DistributedSTO_check_result__isset() : success(false) {}
  bool success :1;
} _DistributedSTO_check_result__isset;

class DistributedSTO_check_result {
 public:

  DistributedSTO_check_result(const DistributedSTO_check_result&);
  DistributedSTO_check_result& operator=(const DistributedSTO_check_result&);
  DistributedSTO_check_result() : success(0) {
  }

  virtual ~DistributedSTO_check_result() throw();
  bool success;

  _DistributedSTO_check_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const DistributedSTO_check_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_check_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_check_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _DistributedSTO_check_presult__isset {
  _DistributedSTO_check_presult__isset() : success(false) {}
  bool success :1;
} _DistributedSTO_check_presult__isset;

class DistributedSTO_check_presult {
 public:


  virtual ~DistributedSTO_check_presult() throw();
  bool* success;

  _DistributedSTO_check_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DistributedSTO_install_args__isset {
  _DistributedSTO_install_args__isset() : tuid(false), tid(false), objid_data_pairs(false) {}
  bool tuid :1;
  bool tid :1;
  bool objid_data_pairs :1;
} _DistributedSTO_install_args__isset;

class DistributedSTO_install_args {
 public:

  DistributedSTO_install_args(const DistributedSTO_install_args&);
  DistributedSTO_install_args& operator=(const DistributedSTO_install_args&);
  DistributedSTO_install_args() : tuid(0), tid(0) {
  }

  virtual ~DistributedSTO_install_args() throw();
  int64_t tuid;
  int64_t tid;
  std::map<int64_t, std::string>  objid_data_pairs;

  _DistributedSTO_install_args__isset __isset;

  void __set_tuid(const int64_t val);

  void __set_tid(const int64_t val);

  void __set_objid_data_pairs(const std::map<int64_t, std::string> & val);

  bool operator == (const DistributedSTO_install_args & rhs) const
  {
    if (!(tuid == rhs.tuid))
      return false;
    if (!(tid == rhs.tid))
      return false;
    if (!(objid_data_pairs == rhs.objid_data_pairs))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_install_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_install_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_install_pargs {
 public:


  virtual ~DistributedSTO_install_pargs() throw();
  const int64_t* tuid;
  const int64_t* tid;
  const std::map<int64_t, std::string> * objid_data_pairs;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_install_result {
 public:

  DistributedSTO_install_result(const DistributedSTO_install_result&);
  DistributedSTO_install_result& operator=(const DistributedSTO_install_result&);
  DistributedSTO_install_result() {
  }

  virtual ~DistributedSTO_install_result() throw();

  bool operator == (const DistributedSTO_install_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const DistributedSTO_install_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_install_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_install_presult {
 public:


  virtual ~DistributedSTO_install_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _DistributedSTO_abort_args__isset {
  _DistributedSTO_abort_args__isset() : tuid(false) {}
  bool tuid :1;
} _DistributedSTO_abort_args__isset;

class DistributedSTO_abort_args {
 public:

  DistributedSTO_abort_args(const DistributedSTO_abort_args&);
  DistributedSTO_abort_args& operator=(const DistributedSTO_abort_args&);
  DistributedSTO_abort_args() : tuid(0) {
  }

  virtual ~DistributedSTO_abort_args() throw();
  int64_t tuid;

  _DistributedSTO_abort_args__isset __isset;

  void __set_tuid(const int64_t val);

  bool operator == (const DistributedSTO_abort_args & rhs) const
  {
    if (!(tuid == rhs.tuid))
      return false;
    return true;
  }
  bool operator != (const DistributedSTO_abort_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_abort_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_abort_pargs {
 public:


  virtual ~DistributedSTO_abort_pargs() throw();
  const int64_t* tuid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_abort_result {
 public:

  DistributedSTO_abort_result(const DistributedSTO_abort_result&);
  DistributedSTO_abort_result& operator=(const DistributedSTO_abort_result&);
  DistributedSTO_abort_result() {
  }

  virtual ~DistributedSTO_abort_result() throw();

  bool operator == (const DistributedSTO_abort_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const DistributedSTO_abort_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const DistributedSTO_abort_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class DistributedSTO_abort_presult {
 public:


  virtual ~DistributedSTO_abort_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class DistributedSTOClient : virtual public DistributedSTOIf {
 public:
  DistributedSTOClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  DistributedSTOClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void read(std::string& _return, const int64_t objid);
  void send_read(const int64_t objid);
  void recv_read(std::string& _return);
  bool lock(const int64_t tuid, const std::vector<int64_t> & objids);
  void send_lock(const int64_t tuid, const std::vector<int64_t> & objids);
  bool recv_lock();
  bool check(const int64_t tuid, const std::map<int64_t, int64_t> & objid_ver_pairs);
  void send_check(const int64_t tuid, const std::map<int64_t, int64_t> & objid_ver_pairs);
  bool recv_check();
  void install(const int64_t tuid, const int64_t tid, const std::map<int64_t, std::string> & objid_data_pairs);
  void send_install(const int64_t tuid, const int64_t tid, const std::map<int64_t, std::string> & objid_data_pairs);
  void recv_install();
  void abort(const int64_t tuid);
  void send_abort(const int64_t tuid);
  void recv_abort();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class DistributedSTOProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<DistributedSTOIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (DistributedSTOProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_read(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_lock(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_check(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_install(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_abort(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  DistributedSTOProcessor(boost::shared_ptr<DistributedSTOIf> iface) :
    iface_(iface) {
    processMap_["read"] = &DistributedSTOProcessor::process_read;
    processMap_["lock"] = &DistributedSTOProcessor::process_lock;
    processMap_["check"] = &DistributedSTOProcessor::process_check;
    processMap_["install"] = &DistributedSTOProcessor::process_install;
    processMap_["abort"] = &DistributedSTOProcessor::process_abort;
  }

  virtual ~DistributedSTOProcessor() {}
};

class DistributedSTOProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  DistributedSTOProcessorFactory(const ::boost::shared_ptr< DistributedSTOIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< DistributedSTOIfFactory > handlerFactory_;
};

class DistributedSTOMultiface : virtual public DistributedSTOIf {
 public:
  DistributedSTOMultiface(std::vector<boost::shared_ptr<DistributedSTOIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~DistributedSTOMultiface() {}
 protected:
  std::vector<boost::shared_ptr<DistributedSTOIf> > ifaces_;
  DistributedSTOMultiface() {}
  void add(boost::shared_ptr<DistributedSTOIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void read(std::string& _return, const int64_t objid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->read(_return, objid);
    }
    ifaces_[i]->read(_return, objid);
    return;
  }

  bool lock(const int64_t tuid, const std::vector<int64_t> & objids) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->lock(tuid, objids);
    }
    return ifaces_[i]->lock(tuid, objids);
  }

  bool check(const int64_t tuid, const std::map<int64_t, int64_t> & objid_ver_pairs) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->check(tuid, objid_ver_pairs);
    }
    return ifaces_[i]->check(tuid, objid_ver_pairs);
  }

  void install(const int64_t tuid, const int64_t tid, const std::map<int64_t, std::string> & objid_data_pairs) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->install(tuid, tid, objid_data_pairs);
    }
    ifaces_[i]->install(tuid, tid, objid_data_pairs);
  }

  void abort(const int64_t tuid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->abort(tuid);
    }
    ifaces_[i]->abort(tuid);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class DistributedSTOConcurrentClient : virtual public DistributedSTOIf {
 public:
  DistributedSTOConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  DistributedSTOConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void read(std::string& _return, const int64_t objid);
  int32_t send_read(const int64_t objid);
  void recv_read(std::string& _return, const int32_t seqid);
  bool lock(const int64_t tuid, const std::vector<int64_t> & objids);
  int32_t send_lock(const int64_t tuid, const std::vector<int64_t> & objids);
  bool recv_lock(const int32_t seqid);
  bool check(const int64_t tuid, const std::map<int64_t, int64_t> & objid_ver_pairs);
  int32_t send_check(const int64_t tuid, const std::map<int64_t, int64_t> & objid_ver_pairs);
  bool recv_check(const int32_t seqid);
  void install(const int64_t tuid, const int64_t tid, const std::map<int64_t, std::string> & objid_data_pairs);
  int32_t send_install(const int64_t tuid, const int64_t tid, const std::map<int64_t, std::string> & objid_data_pairs);
  void recv_install(const int32_t seqid);
  void abort(const int64_t tuid);
  int32_t send_abort(const int64_t tuid);
  void recv_abort(const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif



#endif