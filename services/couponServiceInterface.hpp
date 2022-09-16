#ifndef CS_INTERFACE
#define CS_INTERFACE
#include <string>
#include "../models/coupon.hpp"
using namespace std;

class CouponServiceInterface{
public:
  virtual void createCoupon(string cid){}
  virtual int couponExists(string cid){return 0;}
  virtual string getCouponDetails(string cid){return "";}
  virtual Coupon* getCoupon(string cid){return NULL;}
};
#endif
