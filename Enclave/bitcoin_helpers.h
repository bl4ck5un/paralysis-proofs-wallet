#ifndef PARALYSIS_PROOF_BITCOIN_HELPERS_H
#define PARALYSIS_PROOF_BITCOIN_HELPERS_H

#include "bitcoin/base58.h"
#include "bitcoin/key.h"
#include "bitcoin/script/script.h"
#include "bitcoin/streams.h"
#include "bitcoin/utilstrencodings.h"
#include "utils.h"
#include <bitcoin/primitives/transaction.h>
#include <cstdio>
#include <tlibc/mbusafecrt.h>
#include <vector>

std::string ScriptToAsmStr(const CScript &script);
std::string ScriptToStr(const CScript &script);
CScript generate_simple_cltv_script(const CPubKey &pubkey, uint32_t lockTime);
CScript generate_deposit_script(const CPubKey &userPubkey,
                                const CPubKey &exchPubkey, uint32_t lockTime);
CBitcoinAddress script_to_address(const CScript &script);
bool validate_redeemScript(const CScript &redeemScript,
                           const CScript &scriptPubKey);
CTransaction decode_transaction_from_hex(const std::string &strHexTx,
                                         bool fTryNoWitness = false);

// used for testing
CKey secret_key_from_string_hash(const std::string &str);

class OutPointWithTx {
private:
  CTransactionRef tx;
  uint32_t nOut;
  COutPoint _outpoint;

public:
  OutPointWithTx(const std::string &tx_hex, const CScript &targetScritPubkey)
      : OutPointWithTx(decode_transaction_from_hex(tx_hex), targetScritPubkey) {
  }
  OutPointWithTx(const CTransaction &tx, const CScript &targetScriptPubkey)
      : tx(MakeTransactionRef(tx)) {

    nOut = 66;
    for (uint32_t i = 0; i < tx.vout.size(); i++) {
      if (tx.vout[i].scriptPubKey == targetScriptPubkey) {
        nOut = i;
      }
    }

    MUST_TRUE(nOut != 66);

    _outpoint = COutPoint(GetTxid(), nOut);
  }
  const uint256 &GetTxid() const { return tx.get()->GetHash(); }
  const COutPoint &GetOutPoint() const { return _outpoint; }
  const CTxOut &GetPrevOut() const { return tx.get()->vout[nOut]; }
};

using bytes = std::vector<unsigned char>;

inline size_t tx_size(size_t nin, size_t nout) {
  return 4 + 2 + nin * 153 + 1 + nout * 34 + 4;
}

inline std::string tx2hex(const CTransaction &t) {
  CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
  ss << t;

  return HexStr(ss);
}

#include "message.h"

inline size_t tx2arbuf(uint8_t *dst, const CTransaction &t) {
  CDataStream ss(SER_NETWORK, PROTOCOL_VERSION);
  ss << t;

  memcpy_s(dst, AR_BUF_SIZE, ss.data(), ss.size());

  return ss.size();
}

#endif // PARALYSIS_PROOF_BITCOIN_HELPERS_H
