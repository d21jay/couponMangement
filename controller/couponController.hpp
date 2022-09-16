#ifndef CC_HPP
#define CC_HPP
#include "../services/couponServiceInterface.hpp"
#include "../factory/couponFactory.hpp"
#include "../factory/couponServiceEnum.hpp"
#include "../models/CouponEnum.hpp"
#include <iostream>
class CouponController{
  CouponFactory* couponFactory = new CouponFactory;
public:
  void createCoupon(string cid);
  int couponExists(string cid);
  string getCouponDetails(string cid);
  Coupon* getCoupon(string cid);
};
#endif
