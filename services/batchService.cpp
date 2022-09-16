#include "batchService.hpp"

void BatchService::createOpenBatch(string batchId, time_t validity, string distributorId, int maxGrants){
  time_t current = time(0);
  if(validity < current || maxGrants < 1) {
    throw INVALID_REQUEST::msg;
  }
  else {
    if(this->batchDict.find(batchId) != this->batchDict.end()) {
        throw BATCH_ALREADY_EXIST::msg;
    }
    else {
      Batch* batch = new Batch();
      batch->setBatchId(batchId);
      batch->setValidityPeriod(validity);
      batch->setDistributorId(distributorId);
      batch->setRemainingGrants(maxGrants);
      batch->setCouponType(OPEN);
      this->batchDict.insert({batchId, batch});
    }
  }
}
void BatchService::createClosedBatch(string batchId, time_t validity, string distributorId){
  time_t current = time(0);
  if(validity < current) {
    throw INVALID_REQUEST::msg;
  }
  else {
    if(this->batchDict.find(batchId) != this->batchDict.end()) {
        throw BATCH_ALREADY_EXIST::msg;
    }
    else {
      Batch* batch = new Batch();
      batch->setBatchId(batchId);
      batch->setValidityPeriod(validity);
      batch->setDistributorId(distributorId);
      batch->setCouponType(CLOSED);
      this->batchDict.insert({batchId, batch});
    }
  }
}
void BatchService::ingestCoupons(string batchId, unordered_set<string> coupons){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
      unordered_set<string> existing = this->batchDict[batchId]->getCoupons();
      for(string x : coupons){
        existing.insert(x);
      }
      this->batchDict[batchId]->setCoupons(existing);
  }
  else {
    throw INVALID_BATCH::msg;
  }
}
void BatchService::updateState(string batchId, BatchState batchState){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
      this->batchDict[batchId]->setBatchState(batchState);
  }
  else {
    throw INVALID_BATCH::msg;
  }
}
string BatchService::grantCoupon(string batchId){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
    if(this->batchDict[batchId]->getBatchState() != ACTIVE){
      throw BATCH_NOT_ACTIVE::msg;
    }
    else {
      unordered_set<string> existing = this->batchDict[batchId]->getCoupons();
      if(existing.size() == 0) {
        throw BATCH_EXHAUSTED::msg;
      }
      else {
        string cid = *(existing.begin());
        try{
          this->useCoupon(batchId, cid);
        }
        catch(string exp) {
          throw exp;
        }
        return cid;
      }
    }
  }
  else {
    throw INVALID_BATCH::msg;
  }
}
void BatchService::useCoupon(string batchId, string couponId){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
      time_t current = time(0);
      time_t batchTime = this->batchDict[batchId]->getValidityPeriod();
      if(current > batchTime) {
        this->updateState(batchId, EXPIRED);
      }
      if(this->batchDict[batchId]->getBatchState() != ACTIVE){
        throw BATCH_NOT_ACTIVE::msg;
      }
      else {
        unordered_set<string> existing = this->batchDict[batchId]->getCoupons();
        unordered_set<string> granted = this->batchDict[batchId]->getGrantedCoupons();
        int x = this->batchDict[batchId]->getRemainingGrants();
        if(this->batchDict[batchId]->getCouponType() == OPEN && x < 1) {
          throw GRANT_LIMIT_REACHED::msg;
        }
        else {
          if(existing.find(couponId) != existing.end()) {
            existing.erase(couponId);
            granted.insert(couponId);
            this->batchDict[batchId]->setCoupons(existing);
            this->batchDict[batchId]->setGrantedCoupons(granted);
            if(this->batchDict[batchId]->getCouponType() == OPEN){
              this->batchDict[batchId]->setRemainingGrants(x - 1);
            }
          }
          else{
            throw COUPON_NOT_IN_BATCH::msg;
          }
        }
      }
  }
  else {
    throw INVALID_BATCH::msg;
  }
}
string BatchService::getBatchDetails(string batchId){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
      string s = "\n batchId: " + batchId + "\n";
      s += "distributorId: " + this->batchDict[batchId]->getDistributorId() + "\n";
      s += "state (1 for active): " + to_string(this->batchDict[batchId]->getBatchState()) + "\n";
      s += "validity: " + to_string(this->batchDict[batchId]->getValidityPeriod()) + "\n";
      s += "unGrantedCoupons: " + to_string(this->batchDict[batchId]->getCoupons().size()) + "\n";
      s += "grantedCoupons: " + to_string(this->batchDict[batchId]->getGrantedCoupons().size()) + "\n";
      s += "is CLOSED CouponType: " + to_string(this->batchDict[batchId]->getCouponType()) + "\n";
      s += "remainingGrants(only valid for OPEN): " + to_string(this->batchDict[batchId]->getRemainingGrants()) + "\n \n";
      return s;
  }
  else {
    throw INVALID_BATCH::msg;
  }
}

int BatchService::getCouponsCount(string batchId){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
      return this->batchDict[batchId]->getRemainingGrants();
  }
  else {
    throw INVALID_BATCH::msg;
  }
}

unordered_set<string> BatchService::getUningestedCoupons(string batchId){
  if(this->batchDict.find(batchId) != this->batchDict.end()) {
      return this->batchDict[batchId]->getCoupons();
  }
  else {
    throw INVALID_BATCH::msg;
  }
}
