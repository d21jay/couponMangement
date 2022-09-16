#include "couponController.hpp"

void CouponController::createCoupon(string cid){
  CouponServiceInterface* si = this->couponFactory->resService((CouponServiceType) COUPON_SERVICE);
  if(si != NULL) {
    try {
      si->createCoupon(cid);
    }
    catch(string exp) {
      cout<<exp;
    }
  }
}
int CouponController::couponExists(string cid){
  CouponServiceInterface* si = this->couponFactory->resService((CouponServiceType) COUPON_SERVICE);
  int x = 0;
  if(si != NULL) {
    try {
      x = si->couponExists(cid);
    }
    catch(string exp) {
      cout<<exp;
    }
  }
  return x;
}
string CouponController::getCouponDetails(string cid){
  CouponServiceInterface* si = this->couponFactory->resService((CouponServiceType) COUPON_SERVICE);
  string s = "";
  if(si != NULL) {
    try {
      s = si->getCouponDetails(cid);
    }
    catch(string exp) {
      cout<<exp;
    }
  }
  return s;
}
Coupon* CouponController::getCoupon(string cid){
  CouponServiceInterface* si = this->couponFactory->resService((CouponServiceType) COUPON_SERVICE);
  Coupon* coupon = NULL;
  if(si != NULL) {
    try {
      coupon = si->getCoupon(cid);
    }
    catch(string exp) {
      cout<<exp;
    }
  }
  return coupon;
}
