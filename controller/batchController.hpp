#ifndef BC_HPP
#define BC_HPP
#include "../services/batchServiceInterface.hpp"
#include "../factory/batchFactory.hpp"
#include "../factory/batchServiceEnum.hpp"
#include "couponController.hpp"
#include "../models/CouponEnum.hpp"
#include "../models/BatchEnum.hpp"
#include <iostream>
class BatchController{
  BatchFactory* batchFactory = new BatchFactory;
public:
  void createOpenBatch(string batchId, time_t validity, string distributorId, int maxGrants);
  void createClosedBatch(string batchId, time_t validity, string distributorId);
  void ingestCoupons(string batchId, unordered_set<string> coupons, CouponController* couponController);
  void updateState(string batchId, BatchState batchState);
  Coupon* grantCoupon(string batchId, CouponController* couponController);
  void useCoupon(string batchId, string couponId);
  string getBatchDetails(string batchId);
  int getCouponsCount(string batchId);
};
#endif
