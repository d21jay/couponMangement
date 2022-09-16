#include "batchFactory.hpp"

BatchServiceInterface* BatchFactory::resService(BatchServiceType ser){
    switch(ser){
      case BATCH_SERVICE:
        return this->batchService;
      break;
      default:
        return NULL;
    }
}
