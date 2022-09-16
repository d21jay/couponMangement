#ifndef BATCH_HPP
#define BATCH_HPP
#include <string>
#include <ctime>
#include "CouponEnum.hpp"
#include "BatchEnum.hpp"
#include <unordered_set>
using namespace std;

class Batch{
  string batchId;
  BatchState batchState = CREATED;
  time_t validityPeriod = time(0);
  string distributorId;
  unordered_set<string> coupons;
  unordered_set<string> grantedCoupons;
  CouponType couponType = OPEN;
  int remainingGrants = 0;
public:
  void setBatchId(string batchId);
  string getBatchId();
  void setBatchState(BatchState batchState);
  BatchState getBatchState();
  void setValidityPeriod(time_t validity);
  time_t getValidityPeriod();

  void setDistributorId(string distributorId);
  string getDistributorId();

  void setCoupons(unordered_set<string> coupons);
  unordered_set<string> getCoupons();
  void setGrantedCoupons(unordered_set<string> coupons);
  unordered_set<string> getGrantedCoupons();

  void setCouponType(CouponType couponType);
  CouponType getCouponType();
  void setRemainingGrants(int x);
  int getRemainingGrants();
};

#endif
