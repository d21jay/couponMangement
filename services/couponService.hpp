#ifndef CS_SERVICE
#define CS_SERVICE
#include "couponServiceInterface.hpp"
#include "../models/coupon.hpp"
#include <unordered_map>
class COUPON_NOT_FOUND {
public:
  inline static const string msg = "ERROR :: coupon not found\n";
};
class COUPON_ALREADY_EXIST {
public:
  inline static const string msg = "ERROR :: coupon already exist\n";
};
class CouponService : public CouponServiceInterface{
  unordered_map<string, Coupon*> couponDict;
public:
  void createCoupon(string cid);
  int couponExists(string cid);
  string getCouponDetails(string cid);
  Coupon* getCoupon(string cid);
};
#endif
