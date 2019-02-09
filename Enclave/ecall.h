#ifndef PARALYSISPROOFS_ECALL_H
#define PARALYSISPROOFS_ECALL_H

#ifdef __cplusplus
extern "C" {
#endif

int parse_wallet_info(const char *_redeemScript, const char *_walletUtxoTx);

#ifdef __cplusplus
};
#endif

#endif // PARALYSISPROOFS_ECALL_H
