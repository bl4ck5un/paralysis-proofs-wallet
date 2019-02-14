#include "utils.h"
#include <string>

static char buf[BUFSIZ];

int printf_std(const char *fmt, ...) {
  int ret;
  va_list ap;
  memset(buf, 0x00, BUFSIZ);
  va_start(ap, fmt);
  ret = vsnprintf(buf, BUFSIZ, fmt, ap);
  MUST_TRUE(ret < BUFSIZ);
  va_end(ap);
  ocall_print_to_std(&ret, buf);
  return ret;
}