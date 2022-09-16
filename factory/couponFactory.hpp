#ifndef COUPONFAC
#define COUPONFAC
#include "../services/couponService.hpp"
#include "couponServiceEnum.hpp"

class CouponFactory{
  CouponService* couponService = new CouponService;
public:
  CouponServiceInterface* resService(CouponServiceType ser);
};
#endif
