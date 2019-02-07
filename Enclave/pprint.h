#include "stddef.h"

#ifndef DEBUG_H_
#define DEBUG_H_

#if defined(__cplusplus)
extern "C" {
#endif

void hexdump(const char *title, void const *data, size_t len);

#if defined(__cplusplus)
}
#endif

#endif