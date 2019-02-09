#ifndef PARALYSISPROOFS_MESSAGE_H
#define PARALYSISPROOFS_MESSAGE_H

#include <stdint.h>
#include <stdlib.h>

#define AR_BUF_SIZE 1024

typedef struct AccusationResult {
  uint8_t* tx1;
  uint8_t* tx2;
  uint8_t * tx_appeal;
  size_t tx1_len;
  size_t tx2_len;
  size_t tx_appeal_len;
} AccusationResult;

#ifdef __cplusplus
extern "C" {
#endif

AccusationResult ar_init();
void ar_free(AccusationResult* ptr);

#ifdef __cplusplus
};
#endif

#endif //PARALYSISPROOFS_MESSAGE_H
