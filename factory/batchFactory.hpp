#ifndef BATCHFAC
#define BATCHFAC
#include "../services/batchService.hpp"
#include "batchServiceEnum.hpp"

class BatchFactory{
  BatchService* batchService = new BatchService;
public:
  BatchServiceInterface* resService(BatchServiceType ser);
};
#endif
