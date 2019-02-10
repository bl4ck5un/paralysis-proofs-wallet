#include "message.h"



AccusationResult accusation_result_init() {
  AccusationResult ar = {NULL, NULL, 0, 0};

  ar.tx1 = malloc(AR_BUF_SIZE);
  ar.tx2 = malloc(AR_BUF_SIZE);

  return ar;
}

void accusation_result_free(AccusationResult *ptr) {
  free(ptr->tx1);
  free(ptr->tx2);
}

AppealResult appeal_result_init() {
  AppealResult r = {NULL, 0};

  r.tx = malloc(AR_BUF_SIZE);
  return r;
}

void appeal_result_free(AppealResult* ptr) {
  free(ptr->tx);
}