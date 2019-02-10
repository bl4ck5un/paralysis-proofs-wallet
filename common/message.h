#ifndef PARALYSISPROOFS_MESSAGE_H
#define PARALYSISPROOFS_MESSAGE_H

#include <stdint.h>
#include <stdlib.h>

#define AR_BUF_SIZE 1024

typedef struct AccusationResult {
  uint8_t* tx1;
  uint8_t* tx2;
  size_t tx1_len;
  size_t tx2_len;
} AccusationResult;


typedef struct AppealResult {
  uint8_t * tx;
  size_t len;
} AppealResult;

#ifdef __cplusplus
extern "C" {
#endif

AccusationResult accusation_result_init();
void accusation_result_free(AccusationResult *ptr);

AppealResult appeal_result_init();
void appeal_result_free(AppealResult* ptr);

#ifdef __cplusplus
};
#endif

#endif //PARALYSISPROOFS_MESSAGE_H
