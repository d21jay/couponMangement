#include "couponService.hpp"
void CouponService::createCoupon(string cid){
  if(this->couponDict.find(cid) != this->couponDict.end()) {
      throw COUPON_ALREADY_EXIST::msg;
  }
  else {
    Coupon* coupon = new Coupon();
    coupon->setCouponId(cid);
    this->couponDict.insert({cid, coupon});
  }
}
int CouponService::couponExists(string cid){
  if(this->couponDict.find(cid) != this->couponDict.end()) {
    return 1;
  }
  else return 0;
}
string CouponService::getCouponDetails(string cid){
  Coupon* coupon = this->getCoupon(cid);
  string s = "";
  if(coupon != NULL) {
    //logic here for more coupon details
    s = coupon->getCouponId();
  }
  return s;
}
Coupon* CouponService::getCoupon(string cid){
  if(this->couponDict.find(cid) != this->couponDict.end()) {
      return this->couponDict[cid];
  }
  else {
    throw COUPON_NOT_FOUND::msg;
  }
}
