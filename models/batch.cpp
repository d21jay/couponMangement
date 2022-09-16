#include "batch.hpp"
void Batch::setBatchId(string batchId){
  this->batchId = batchId;
}
string Batch::getBatchId(){
  return this->batchId;
}
void Batch::setBatchState(BatchState batchState){
  this->batchState = batchState;
}
BatchState Batch::getBatchState(){
  return this->batchState;
}
void Batch::setValidityPeriod(time_t validity){
  this->validityPeriod = validity;
}
time_t Batch::getValidityPeriod(){
  return this->validityPeriod;
}

void Batch::setDistributorId(string distributorId){
  this->distributorId = distributorId;
}
string Batch::getDistributorId(){
  return this->distributorId;
}

void Batch::setCoupons(unordered_set<string> coupons){
  this->coupons = coupons;
}
unordered_set<string> Batch::getCoupons(){
  return this->coupons;
}

void Batch::setGrantedCoupons(unordered_set<string> coupons){
  this->grantedCoupons = coupons;
}
unordered_set<string> Batch::getGrantedCoupons(){
  return this->grantedCoupons;
}

void Batch::setCouponType(CouponType couponType){
  this->couponType = couponType;
}
CouponType Batch::getCouponType(){
  return this->couponType;
}
void Batch::setRemainingGrants(int x){
  this->remainingGrants = x;
}
int Batch::getRemainingGrants(){
  return this->remainingGrants;
}
