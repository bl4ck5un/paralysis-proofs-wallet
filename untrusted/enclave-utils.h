#ifndef EXCH_UTILS_H
#define EXCH_UTILS_H

#include "sgx_eid.h" /* sgx_enclave_id_t */
#include "sgx_error.h"

#include <string>

#define TOKEN_FILENAME "enclave.token"
#define ENCLAVE_FILENAME "enclave.signed.so"

#define LOGGING_CONF "logging.conf"

#if defined(__cplusplus)
extern "C" {
#endif

int ocall_print_to_std(const char *str);
int ocall_print_to_err(const char *str);

#if defined(__cplusplus)
}
#endif

void print_error_message(sgx_status_t ret);
int initialize_enclave(sgx_enclave_id_t *eid);
int initialize_enclave(std::string enclave_path, sgx_enclave_id_t *eid);

std::string readTextFile(const std::string &fname);
std::vector<uint8_t> readBinaryFile(const std::string &fname);

typedef struct _sgx_errlist_t {
  sgx_status_t err;
  const char *msg;
  const char *sug;
} sgx_errlist_t;

/* Error code returned by sgx_create_enclave */
const sgx_errlist_t sgx_errlist[] = {
    {SGX_ERROR_UNEXPECTED, "Unexpected error occurred.", NULL},
    {SGX_ERROR_INVALID_PARAMETER, "Invalid parameter.", NULL},
    {SGX_ERROR_OUT_OF_MEMORY, "Out of memory.", NULL},
    {SGX_ERROR_ENCLAVE_LOST, "Power transition occurred.",
     "Please refer to the sample \"PowerTransition\" for details."},
    {SGX_ERROR_INVALID_ENCLAVE, "Invalid enclave image.", NULL},
    {SGX_ERROR_INVALID_ENCLAVE_ID, "Invalid enclave identification.", NULL},
    {SGX_ERROR_INVALID_SIGNATURE, "Invalid enclave signature.", NULL},
    {SGX_ERROR_OUT_OF_EPC, "Out of EPC memory.", NULL},
    {SGX_ERROR_NO_DEVICE, "Invalid SGX device.",
     "Please make sure SGX module is enabled in the BIOS, and install SGX "
     "driver afterwards."},
    {SGX_ERROR_MEMORY_MAP_CONFLICT, "Memory map conflicted.", NULL},
    {SGX_ERROR_INVALID_METADATA, "Invalid enclave metadata.", NULL},
    {SGX_ERROR_DEVICE_BUSY, "SGX device was busy.", NULL},
    {SGX_ERROR_INVALID_VERSION, "Enclave version was invalid.", NULL},
    {SGX_ERROR_INVALID_ATTRIBUTE, "Enclave was not authorized.", NULL},
    {SGX_ERROR_ENCLAVE_FILE_ACCESS, "Can't open enclave file.", NULL},
};

#include <iomanip>
#include <sstream>

inline std::string hexStr(unsigned char *data, size_t len) {
  std::stringstream ss;
  ss << std::hex;
  for (size_t i = 0; i < len; ++i)
    ss << std::setw(2) << std::setfill('0') << (int)data[i];
  return ss.str();
}

#endif
