#ifndef BS_INTERFACE
#define BS_INTERFACE
#include <string>
#include <ctime>
#include "../models/BatchEnum.hpp"
#include <unordered_set>
using namespace std;

class BatchServiceInterface{
public:
  virtual void createOpenBatch(string batchId, time_t validity, string distributorId, int maxGrants){}
  virtual void createClosedBatch(string batchId, time_t validity, string distributorId){}
  virtual void ingestCoupons(string batchId, unordered_set<string> coupons){}
  virtual void updateState(string batchId, BatchState batchState){}
  virtual string grantCoupon(string batchId){return "";}
  virtual void useCoupon(string batchId, string couponId){}
  virtual string getBatchDetails(string batchId){return "";}
  virtual int getCouponsCount(string batchId){return 0;}
  virtual unordered_set<string> getUningestedCoupons(string batchId){
    unordered_set<string> s;
    return s;
  }
};
#endif
