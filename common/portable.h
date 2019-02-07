#ifndef PARALYSIS_PROOF_PORTABLE_H
#define PARALYSIS_PROOF_PORTABLE_H

#ifdef IN_ENCLAVE
#include "../Enclave/utils.h"
#define printf_sgx printf_std
#else
#include <stdio.h>
#define printf_sgx printf
#endif

#endif // PARALYSIS_PROOF_PORTABLE_H
