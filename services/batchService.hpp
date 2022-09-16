#ifndef BS_SERVICE
#define BS_SERVICE
#include "batchServiceInterface.hpp"
#include "../models/batch.hpp"
#include <unordered_map>
class INVALID_REQUEST {
public:
  inline static const string msg = "ERROR :: invalid request //TODO::sub-errors\n";
};
class INVALID_BATCH {
public:
  inline static const string msg = "ERROR :: invalid batch\n";
};
class BATCH_ALREADY_EXIST {
public:
  inline static const string msg = "ERROR :: batch already exists\n";
};
class BATCH_NOT_ACTIVE {
public:
  inline static const string msg = "ERROR :: batch not active\n";
};
class BATCH_EXHAUSTED {
public:
  inline static const string msg = "ERROR :: batch exhausted\n";
};
class COUPON_NOT_IN_BATCH {
public:
  inline static const string msg = "ERROR :: coupon not in batch\n";
};
class GRANT_LIMIT_REACHED {
public:
  inline static const string msg = "ERROR :: grant limit reached\n";
};
class BatchService : public BatchServiceInterface{
  unordered_map<string, Batch*> batchDict;
public:
  void createOpenBatch(string batchId, time_t validity, string distributorId, int maxGrants);
  void createClosedBatch(string batchId, time_t validity, string distributorId);
  void ingestCoupons(string batchId, unordered_set<string> coupons);
  void updateState(string batchId, BatchState batchState);
  string grantCoupon(string batchId);
  void useCoupon(string batchId, string couponId);
  string getBatchDetails(string batchId);
  int getCouponsCount(string batchId);
  unordered_set<string> getUningestedCoupons(string batchId);
};
#endif
