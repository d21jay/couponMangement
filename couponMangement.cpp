#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "controller/batchController.hpp"
#include "controller/couponController.hpp"

int main(){
  BatchController* batchController = new BatchController;
  CouponController* couponController = new CouponController;
  cout<<"app is alive\n";
  cout<<"testing\n";
  string temp;
  cout<<"------------------  testing OPEN batches creation and ingestion first -----------------\n";
  cout<<"TEST :: creating normal OPEN batch with batchId = '123' and expiration of 10000 sec in future and with maxGrant of 4."<<endl;
  batchController->createOpenBatch("123", time(0) + 10000, "Jay", 4);
  cout<<"TEST :: retriving batch details of batch '123'"<<endl;
  temp = batchController->getBatchDetails("123");
  cout<<temp;
  cout<<"TEST :: storing some coupon codes in batch '123' with code 'c1', 'c2', 'c3', 'c4', 'c5'\n";
  unordered_set<string> cs1({"c1", "c2", "c3", "c4", "c5"});
  batchController->ingestCoupons("123", cs1, couponController);
  cout<<"TEST :: setting state of batch '123' to ACTIVE"<<endl;
  batchController->updateState("123", ACTIVE);
  cout<<"TEST :: retriving batch details of batch '123'"<<endl;
  temp = batchController->getBatchDetails("123");
  cout<<temp;

  cout<<"TEST :: creating normal OPEN batch with batchId = '234' and expiration of 500 sec in future and with maxGrant of 6."<<endl;
  batchController->createOpenBatch("234", time(0) + 500, "Jay", 6);
  cout<<"TEST :: retriving batch details of batch '234'"<<endl;
  temp = batchController->getBatchDetails("234");
  cout<<temp;
  cout<<"TEST :: storing some coupon codes in batch '234' with code 'c11', 'c21', 'c3', 'c4' : It should fail\n";
  unordered_set<string> cs2({"c11", "c21", "c3", "c4"});
  batchController->ingestCoupons("234", cs2, couponController);
  cout<<"TEST :: setting state of batch '234' to ACTIVE"<<endl;
  batchController->updateState("234", ACTIVE);
  cout<<"TEST :: retriving batch details of batch '234'"<<endl;
  temp = batchController->getBatchDetails("234");
  cout<<temp;

  cout<<"TEST :: RETRYING to store some coupon codes in batch '234' with code 'c11', 'c21', 'c32', 'c42' : It should be successful now\n";
  unordered_set<string> cs3({"c11", "c21", "c32", "c42"});
  batchController->ingestCoupons("234", cs3, couponController);
  cout<<"TEST :: retriving batch details of batch '234'"<<endl;
  temp = batchController->getBatchDetails("234");
  cout<<temp;

  cout<<"TEST :: attempting RECREATING normal OPEN batch with batchId = '123' and expiration of 100 sec in future and with maxGrant of 10. It should fail"<<endl;
  batchController->createOpenBatch("123", time(0) + 10000, "Jay", 4);

  cout<<"TEST :: attempting to create OPEN batch with invalid input, say maxGrant of -1\n";
  batchController->createOpenBatch("567", time(0) + 10000, "Jay", -1);

  cout<<"------------------  testing closed batches creation and ingestion now -----------------\n";
  cout<<"TEST :: creating CLOSED batch with batchId = '521' and expiration of 10000 sec in future."<<endl;
  batchController->createClosedBatch("521", time(0) + 10000, "Someone");
  cout<<"TEST :: retriving batch details of batch '521'"<<endl;
  temp = batchController->getBatchDetails("521");
  cout<<temp;
  cout<<"TEST :: storing some coupon codes in batch '123' with code 'c52', 'c53'\n";
  unordered_set<string> cs4({"c52", "c53"});
  batchController->ingestCoupons("521", cs4, couponController);
  cout<<"TEST :: setting state of batch '521' to ACTIVE"<<endl;
  batchController->updateState("521", ACTIVE);
  cout<<"TEST :: retriving batch details of batch '521'"<<endl;
  temp = batchController->getBatchDetails("521");
  cout<<temp;
  cout<<"TEST :: attempting to create CLOSED batch with invalid input, say expiration in past"<<endl;
  batchController->createClosedBatch("967", time(0) - 10000, "Jay");

  cout<<"------------------  testing ingestions -----------------\n";
  cout<<"TEST:: lets get a coupon from batch 123 first"<<endl;
  Coupon* coupon = batchController->grantCoupon("123", couponController);
  //calling coupon here directly for quick re-verification. Not a functionality to get couponId;
  cout<<"reverifying the records of this coupon: "<<couponController->getCouponDetails(coupon->getCouponId())<<endl;
  cout<<"TEST:: lets get 2nd coupon from batch 123."<<endl;
  coupon = batchController->grantCoupon("123", couponController);
  cout<<"TEST :: retriving batch details of batch '123'. ungranted coupon count should be now 3. and granted should be 2."<<endl;
  temp = batchController->getBatchDetails("123");
  cout<<temp;

  cout<<"TEST:: lets try to get coupon from batch '123' 4 more times."<<endl;
  cout<<"attempt1: \n";
  batchController->grantCoupon("123", couponController);
  cout<<"attempt2: \n";
  batchController->grantCoupon("123", couponController);
  cout<<"attempt3: \n";
  batchController->grantCoupon("123", couponController);
  cout<<"attempt4: \n";
  batchController->grantCoupon("123", couponController);
  cout<<"We see that grant limit of 4 is reached here first";
  temp = batchController->getBatchDetails("123");

  cout<<"TEST:: lets try to get coupon from batch '234' 5 times. coupons would be exhausted first."<<endl;
  cout<<"attempt1: \n";
  batchController->grantCoupon("234", couponController);
  cout<<"attempt2: \n";
  batchController->grantCoupon("234", couponController);
  cout<<"attempt3: \n";
  batchController->grantCoupon("234", couponController);
  cout<<"attempt4: \n";
  batchController->grantCoupon("234", couponController);
  cout<<"attempt5: \n";
  batchController->grantCoupon("234", couponController);
  cout<<"retriving details:\n";
  temp = batchController->getBatchDetails("123");
  cout<<temp;
  cout<<"------------------  testing timeout -----------------\n";
  cout<<"TEST :: creating OPEN batch with batchId = '12' and expiration of 1 sec in future and with maxGrant of 4."<<endl;
  batchController->createOpenBatch("12", time(0) + 1, "Jay", 4);
  cout<<"TEST :: retriving batch details of batch '12'"<<endl;
  temp = batchController->getBatchDetails("123");
  cout<<temp;
  cout<<"TEST :: storing some coupon codes in batch '12' with code 'c15', 'c25', 'c35', 'c45', 'c55'\n";
  unordered_set<string> cs6({"c15", "c25", "c35", "c45", "c55"});
  batchController->ingestCoupons("12", cs6, couponController);
  cout<<"TEST :: setting state of batch '12' to ACTIVE"<<endl;
  batchController->updateState("12", ACTIVE);
  cout<<"TEST :: retriving batch details of batch '12'"<<endl;
  temp = batchController->getBatchDetails("12");
  cout<<temp;
  cout<<"TEST:: lets try to get coupon from batch '12' 1 time."<<endl;
  cout<<"attempt1: \n";
  batchController->grantCoupon("12", couponController);
  cout<<"TEST:: now lets sleep for 2 seconds"<<endl;
  sleep(2);
  cout<<"TEST:: lets try to get coupon from batch '12' 2nd time."<<endl;
  cout<<"attempt2: \n";
  batchController->grantCoupon("12", couponController);
  temp = batchController->getBatchDetails("12");
  cout<<temp;
  cout<<"we see now batch is not active. State is 2(which is EXPIRED state)\n";
  cout<<"------------------  testing TERMINATION -----------------\n";
  cout<<"TEST:: lets try to get coupon from batch '521' 1 time."<<endl;
  cout<<"attempt1: \n";
  batchController->grantCoupon("521", couponController);
  batchController->updateState("521", TERMINATED);
  cout<<"TEST:: lets try to get coupon from batch '12' 2nd time."<<endl;
  cout<<"attempt2: \n";
  batchController->grantCoupon("521", couponController);
  temp = batchController->getBatchDetails("521");
  cout<<temp;
  cout<<"we see now batch is not active. State is 4(which is TERMINATED state)\n";
  cout<<"------------------  ending tests -----------------\n";
  return 0;
}
