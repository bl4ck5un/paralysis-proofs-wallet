#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include "sgx_edger8r.h" /* for sgx_satus_t etc. */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
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

#ifndef OCALL_PRINT_TO_STD_DEFINED__
#define OCALL_PRINT_TO_STD_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_to_std, (const char *str));
#endif
#ifndef OCALL_PRINT_TO_ERR_DEFINED__
#define OCALL_PRINT_TO_ERR_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_to_err, (const char *str));
#endif
#ifndef SGX_OC_CPUIDEX_DEFINED__
#define SGX_OC_CPUIDEX_DEFINED__
void SGX_UBRIDGE(SGX_CDECL, sgx_oc_cpuidex,
                 (int cpuinfo[4], int leaf, int subleaf));
#endif
#ifndef SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_wait_untrusted_event_ocall,
                (const void *self));
#endif
#ifndef SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_untrusted_event_ocall,
                (const void *waiter));
#endif
#ifndef SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_setwait_untrusted_events_ocall,
                (const void *waiter, const void *self));
#endif
#ifndef SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_multiple_untrusted_events_ocall,
                (const void **waiters, size_t total));
#endif
#ifndef CREATE_SESSION_OCALL_DEFINED__
#define CREATE_SESSION_OCALL_DEFINED__
sgx_status_t SGX_UBRIDGE(SGX_NOCONVENTION, create_session_ocall,
                         (uint32_t * sid, uint8_t *dh_msg1,
                          uint32_t dh_msg1_size, uint32_t timeout));
#endif
#ifndef EXCHANGE_REPORT_OCALL_DEFINED__
#define EXCHANGE_REPORT_OCALL_DEFINED__
sgx_status_t SGX_UBRIDGE(SGX_NOCONVENTION, exchange_report_ocall,
                         (uint32_t sid, uint8_t *dh_msg2, uint32_t dh_msg2_size,
                          uint8_t *dh_msg3, uint32_t dh_msg3_size,
                          uint32_t timeout));
#endif
#ifndef CLOSE_SESSION_OCALL_DEFINED__
#define CLOSE_SESSION_OCALL_DEFINED__
sgx_status_t SGX_UBRIDGE(SGX_NOCONVENTION, close_session_ocall,
                         (uint32_t sid, uint32_t timeout));
#endif
#ifndef INVOKE_SERVICE_OCALL_DEFINED__
#define INVOKE_SERVICE_OCALL_DEFINED__
sgx_status_t SGX_UBRIDGE(SGX_NOCONVENTION, invoke_service_ocall,
                         (uint8_t * pse_message_req,
                          uint32_t pse_message_req_size,
                          uint8_t *pse_message_resp,
                          uint32_t pse_message_resp_size, uint32_t timeout));
#endif

sgx_status_t enclaveTest(sgx_enclave_id_t eid, int *retval);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
