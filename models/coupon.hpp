#ifndef COUPON_HPP
#define COUPON_HPP
#include <string>
using namespace std;

class Coupon{
  string couponId;
public:
  void setCouponId(string couponId);
  string getCouponId();
};
#endif
