#include "message.h"

AccusationResult ar_init() {
  AccusationResult ar = {NULL, NULL, NULL, 0, 0, 0};

  ar.tx1 = malloc(1024);
  ar.tx2 = malloc(1024);
  ar.tx_appeal = malloc(1024);

  return ar;
}

void ar_free(AccusationResult* ptr) {
  free(ptr->tx1);
  free(ptr->tx2);
  free(ptr->tx_appeal);
}