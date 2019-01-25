#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include "sgx_edger8r.h" /* for sgx_ocall etc. */
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#include "../common/common.h"
#include "sgx_tae_service.h"
#include "sgx_trts.h"
#include "sgx_tseal.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

int enclaveTest(void);

sgx_status_t SGX_CDECL ocall_print_to_std(int *retval, const char *str);
sgx_status_t SGX_CDECL ocall_print_to_err(int *retval, const char *str);
sgx_status_t SGX_CDECL sgx_oc_cpuidex(int cpuinfo[4], int leaf, int subleaf);
sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int *retval,
                                                             const void *self);
sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int *retval,
                                                            const void *waiter);
sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(
    int *retval, const void *waiter, const void *self);
sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(
    int *retval, const void **waiters, size_t total);
sgx_status_t SGX_CDECL create_session_ocall(sgx_status_t *retval, uint32_t *sid,
                                            uint8_t *dh_msg1,
                                            uint32_t dh_msg1_size,
                                            uint32_t timeout);
sgx_status_t SGX_CDECL exchange_report_ocall(
    sgx_status_t *retval, uint32_t sid, uint8_t *dh_msg2, uint32_t dh_msg2_size,
    uint8_t *dh_msg3, uint32_t dh_msg3_size, uint32_t timeout);
sgx_status_t SGX_CDECL close_session_ocall(sgx_status_t *retval, uint32_t sid,
                                           uint32_t timeout);
sgx_status_t SGX_CDECL invoke_service_ocall(sgx_status_t *retval,
                                            uint8_t *pse_message_req,
                                            uint32_t pse_message_req_size,
                                            uint8_t *pse_message_resp,
                                            uint32_t pse_message_resp_size,
                                            uint32_t timeout);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
