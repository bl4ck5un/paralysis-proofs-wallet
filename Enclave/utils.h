#ifndef PARALYSIS_PROOF_ENCLVAE_UTILS_H
#define PARALYSIS_PROOF_ENCLAVE_UTILS_H

#include "Enclave_t.h"

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#define ECALL_WRAPPER_RET(expr)                                                \
  try {                                                                        \
    expr;                                                                      \
    return 0;                                                                  \
  } catch (const std::exception &e) {                                          \
    LL_CRITICAL("error happened: %s", e.what());                               \
    return -1;                                                                 \
  } catch (...) {                                                              \
    LL_CRITICAL("unknown error happened");                                     \
    return -1;                                                                 \
  }

#define CATCH_STD_AND_ALL                                                      \
  catch (const std::exception &e) {                                            \
    LL_CRITICAL("error happened: %s", e.what());                               \
    return -1;                                                                 \
  }                                                                            \
  catch (...) {                                                                \
    LL_CRITICAL("unknown error happened");                                     \
    return -1;                                                                 \
  }

#define CATCHALL_AND(x)                                                        \
  catch (const std::exception &e) {                                            \
    LL_CRITICAL("error happened: %s", e.what());                               \
    (x);                                                                       \
  }                                                                            \
  catch (...) {                                                                \
    LL_CRITICAL("unknown error happened");                                     \
    (x);                                                                       \
  }

#define CATCH_STD_AND_ALL_NO_RET                                               \
  catch (const std::exception &e) {                                            \
    LL_CRITICAL("error happened: %s", e.what());                               \
  }                                                                            \
  catch (...) {                                                                \
    LL_CRITICAL("unknown error happened");                                     \
  }

#define MUST_TRUE(c)                                                           \
  do {                                                                         \
    if (!(c)) {                                                                \
      char buf[BUFSIZ] = {'\0'};                                               \
      snprintf(buf, sizeof buf, "assertion failed at %s:%d",                   \
               strrchr(__FILE__, '/') + 1, __LINE__);                          \
      throw std::runtime_error(buf);                                           \
    }                                                                          \
  } while (false)

using bytes = std::vector<uint8_t>;

#ifdef __cplusplus
extern "C" {
#endif

int printf_std(const char *fmt, ...);

#ifdef __cplusplus
};
#endif

#endif // PARALYSIS_PROOF_UTILS_H
