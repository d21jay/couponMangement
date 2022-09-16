#include "batchController.hpp"

void BatchController::createOpenBatch(string batchId, time_t validity, string distributorId, int maxGrants){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  if(si != NULL) {
    try {
      si->createOpenBatch(batchId, validity, distributorId, maxGrants);
      cout<<"creation successful\n";
    }
    catch(string exp) {
      cout<<exp;
    }
  }
}

void BatchController::createClosedBatch(string batchId, time_t validity, string distributorId){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  if(si != NULL) {
    try {
      si->createClosedBatch(batchId, validity, distributorId);
      cout<<"creation successful\n";
    }
    catch(string exp) {
      cout<<exp;
    }
  }
}

void BatchController::ingestCoupons(string batchId, unordered_set<string> coupons, CouponController* couponController){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  if(si != NULL) {
    try {
      int count = 0;
      int w;
      for(string x :coupons){
        w = couponController->couponExists(x);
        count += w;
        if(w) cout<<"WARNING :: coupon with id: "<<x<<" already exists. Remove from ingestion set\n";
      }
      if(count == 0) {
        cout<<"INFO :: pre-validation successful\n";
        for(string x :coupons){
          couponController->createCoupon(x);
        }
        si->ingestCoupons(batchId, coupons);
        cout<<"ingestion complete\n";
      }
      else cout<<"ERROR :: ingestion aborted.\n";
    }
    catch(string exp) {
      cout<<exp;
    }
  }
}

void BatchController::updateState(string batchId, BatchState batchState){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  if(si != NULL) {
    try {
      si->updateState(batchId, batchState);
      cout<<"successful\n";
    }
    catch(string exp) {
      cout<<exp;
    }
  }
}

Coupon* BatchController::grantCoupon(string batchId, CouponController* couponController){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  Coupon* coupon = NULL;
  if(si != NULL) {
    try {
      string cid = si->grantCoupon(batchId);
      coupon = couponController->getCoupon(cid);
      cout<<"granted coupon with id: "<<cid<<"\n";
    }
    catch(string exp) {
      cout<<exp;
    }
  }
  return coupon;
}

void BatchController::useCoupon(string batchId, string couponId){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  if(si != NULL) {
    try {
      si->useCoupon(batchId, couponId);
      cout<<"successful\n";
    }
    catch(string exp) {
      cout<<exp;
    }
  }
}

string BatchController::getBatchDetails(string batchId){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  string s = "";
  if(si != NULL) {
    try {
      s = si->getBatchDetails(batchId);
    }
    catch(string exp) {
      cout<<exp;
    }
  }
  return s;
}

int BatchController::getCouponsCount(string batchId){
  BatchServiceInterface* si = this->batchFactory->resService((BatchServiceType) BATCH_SERVICE);
  int x = 0;
  if(si != NULL) {
    try {
      x = si->getCouponsCount(batchId);
    }
    catch(string exp) {
      cout<<exp;
    }
  }
  return x;
}
