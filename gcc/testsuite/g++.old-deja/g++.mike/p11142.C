// Build don't run:
// Special g++ Options: -fexceptions -c -O -g
// prms-id: 11142

class RWxmsg {
public:
  RWxmsg();
  virtual ~RWxmsg();
};

class RWTHRInternalError : public RWxmsg {
public:
  virtual ~RWTHRInternalError() { }
};

void setCount(int count) {
  throw RWTHRInternalError();
}
