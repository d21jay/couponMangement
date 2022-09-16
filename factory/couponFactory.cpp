#include "couponFactory.hpp"

CouponServiceInterface* CouponFactory::resService(CouponServiceType ser){
    switch(ser){
      case COUPON_SERVICE:
        return this->couponService;
      break;
      default:
        return NULL;
    }
}
