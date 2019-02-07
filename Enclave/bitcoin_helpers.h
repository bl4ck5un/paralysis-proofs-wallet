#ifndef PARALYSIS_PROOF_BITCOIN_HELPERS_H
#define PARALYSIS_PROOF_BITCOIN_HELPERS_H

#include "bitcoin/base58.h"
#include "bitcoin/key.h"
#include "bitcoin/script/script.h"
#include <bitcoin/primitives/transaction.h>
#include <vector>

std::string ScriptToAsmStr(const CScript &script);
CScript generate_simple_cltv_script(const CPubKey &pubkey, uint32_t lockTime);
CScript generate_deposit_script(const CPubKey &userPubkey,
                                const CPubKey &exchPubkey, uint32_t lockTime);
CBitcoinAddress script_to_address(const CScript &script);
bool validate_redeemScript(const CScript &redeemScript,
                           const CScript &scriptPubKey);
CTransaction decode_transaction_from_hex(const std::string &strHexTx,
                                 bool fTryNoWitness=false);

// used for testing
CKey secret_key_from_string_hash(const std::string &str);

class OutPointWithTx {
private:
  CTransactionRef tx;
  uint32_t nOut;
  COutPoint _outpoint;

public:
  OutPointWithTx(const std::string& tx_hex, const CScript& targetScritPubkey): OutPointWithTx(decode_transaction_from_hex(tx_hex), targetScritPubkey) {}
  OutPointWithTx(const CTransaction &tx, const CScript& targetScriptPubkey)
      : tx(MakeTransactionRef(tx)) {
    for (uint32_t i = 0; i < tx.vout.size(); i++) {
      if (tx.vout[i].scriptPubKey == targetScriptPubkey) {
        nOut = i;
      }
    }

    _outpoint = COutPoint(GetTxid(), nOut);
  }
  const uint256 &GetTxid() const { return tx.get()->GetHash(); }
  const COutPoint& GetOutPoint() const { return _outpoint; }
  const CTxOut& GetPrevOut() const { return tx.get()->vout[nOut]; }
};

#include <stdio.h>

#define MUST_TRUE(c)                                                           \
  do {                                                                         \
    if (!(c)) {                                                                \
      char buf[BUFSIZ] = {'\0'};                                               \
      snprintf(buf, sizeof buf, "assert failed at %s:%d",                      \
               strrchr(__FILE__, '/') + 1, __LINE__);                          \
      throw std::runtime_error(buf);                                           \
    }                                                                          \
  } while (false)

#endif // PARALYSIS_PROOF_BITCOIN_HELPERS_H
