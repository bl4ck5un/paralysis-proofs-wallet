#ifndef PARALYSISPROOFS_PARALYSIS_H
#define PARALYSISPROOFS_PARALYSIS_H

#include <string>

#include "bitcoin_helpers.h"

#include "bitcoin/base58.h"
#include "bitcoin/keystore.h"
#include "bitcoin/policy/policy.h"
#include "bitcoin/pubkey.h"
#include "bitcoin/script/sign.h"

using std::move;
using std::string;

void test_paralysis();

class Party {
private:
  string _name;
  CPubKey pubkey;
  CKey secret;

public:
  Party(const Party &other)
      : _name(other._name), pubkey(other.pubkey.begin(), other.pubkey.end()) {
    secret.Set(other.secret.begin(), other.secret.end(),
               other.secret.IsCompressed());
  }
  explicit Party(const string &name)
      : _name(name), secret(secret_key_from_string_hash(_name)) {
    auto _pubkey = secret.GetPubKey();
    pubkey.Set(_pubkey.begin(), _pubkey.end());
  }

  Party(string name, CPubKey pubkey)
      : _name(move(name)), pubkey(pubkey.begin(), pubkey.end()) {}

  CBitcoinAddress Address() const { return CBitcoinAddress(pubkey.GetID()); }

  const CPubKey &GetPubKey() const { return pubkey; }

  CScript ScriptPubkey() const {
    return GetScriptForDestination(pubkey.GetID());
  }

  const CKey &GetSecret() const { return secret; }

  string ToString() const {
    return "name: " + _name + ", address=" + Address().ToString();
  }
};

class LifeSignal {
private:
  CPubKey key1;
  CKey key2;
  uint32_t relative_timeout;
  CAmount amount;

  CScript _redeemScript;
  CScript _scriptPubkey;

public:
  LifeSignal(const CPubKey &key1, uint32_t relative_timeout)
      : key1(key1.begin(), key1.end()),
        key2(secret_key_from_string_hash("tmp secret")),
        relative_timeout(relative_timeout), amount(0.0001 * COIN) {
    _redeemScript << OP_IF;
    _redeemScript += GetScriptForDestination(key1.GetID());
    _redeemScript << OP_ELSE << relative_timeout << OP_CHECKSEQUENCEVERIFY
                  << OP_DROP;
    _redeemScript += GetScriptForDestination(key2.GetPubKey().GetID());
    _redeemScript << OP_ENDIF;

    _scriptPubkey = GetScriptForDestination(CScriptID(_redeemScript));
  }

  uint32_t GetRelativeTimeout() const { return relative_timeout; }

  const CScript &GetRedeemScript() const { return _redeemScript; }

  const CScript &GetScriptPubKey() const { return _scriptPubkey; }

  const CScript scriptSigByKey1(const CKey &secret,
                                const CMutableTransaction &unsigned_tx,
                                uint32_t which_to_sign) const {
    MUST_TRUE(secret.GetPubKey() == this->key1);
    CScript branch = OP_TRUE;
    auto sighash = SignatureHash(_redeemScript, unsigned_tx, which_to_sign,
                                 SIGHASH_ALL, 0, SIGVERSION_BASE);

    std::vector<unsigned char> vchSig;
    secret.Sign(sighash, vchSig);
    vchSig.push_back((unsigned char)SIGHASH_ALL);

    return CScript() << vchSig << ToByteVector(secret.GetPubKey()) << branch
                     << ToByteVector(_redeemScript);
  }

  const CScript &scriptSigByKey2(const CMutableTransaction &unsigned_tx,
                                 uint32_t which_to_sign) const {
    auto branch = OP_FALSE;
    auto sighash = SignatureHash(_redeemScript, unsigned_tx, which_to_sign,
                                 SIGHASH_ALL, 0, SIGVERSION_BASE);

    bytes vchSig;
    key2.Sign(sighash, vchSig);
    vchSig.push_back((unsigned char)SIGHASH_ALL);

    return CScript() << vchSig << ToByteVector(key2.GetPubKey()) << branch
                     << ToByteVector(_redeemScript);
  }

  CTransaction into_transaction(const CKey &dust_seckey,
                                const OutPointWithTx &dust_op,
                                const CFeeRate &fee_rate) const {
    if (dust_op.GetPrevOut().scriptPubKey !=
        GetScriptForDestination(dust_seckey.GetPubKey().GetID())) {
      throw std::invalid_argument("dust outpoint has incorrect scriptPubkey");
    }

    auto sum_in = dust_op.GetPrevOut().nValue;
    auto fees = fee_rate.GetFee(tx_size(1, 2));
    auto refund = sum_in - fees - this->amount;

    LL_DEBUG("fee: %d", fees);
    LL_DEBUG("amount: %d", (sum_in - fees));

    CMutableTransaction unsigned_tx;
    unsigned_tx.vin.emplace_back(dust_op.GetOutPoint());
    unsigned_tx.vout.emplace_back(amount, _scriptPubkey);
    unsigned_tx.vout.emplace_back(
        refund, GetScriptForDestination(dust_seckey.GetPubKey().GetID()));

    // spend the dust input
    auto _ = std::unique_ptr<ECCVerifyHandle>(new ECCVerifyHandle());
    CBasicKeyStore tmp;
    tmp.AddKey(dust_seckey);
    if (!SignSignature(tmp, dust_op.GetPrevOut().scriptPubKey, unsigned_tx, 0,
                       0, SIGHASH_ALL)) {
      throw std::runtime_error("can't sign the dust input");
    }

    LL_DEBUG("done signing");
    return CTransaction(unsigned_tx);
  }
};

using std::vector;

static opcodetype EncodeOP_N(int n) {
  assert(n >= 0 && n <= 16);
  if (n == 0)
    return OP_0;
  return (opcodetype)(OP_1 + n - 1);
}

class Wallet {
private:
  vector<Party> _users;
  Party _sgx;
  vector<LifeSignal> lift_signals;
  CScript _redeemScript;
  CScript _scriptPubKey;

  CScript sigScriptBySGX(const CKey &sgx_seckey,
                         const CMutableTransaction &unsigned_tx,
                         uint32_t which_to_sign) {
    auto branch = OP_TRUE;
    auto sighash = SignatureHash(_redeemScript, unsigned_tx, which_to_sign,
                                 SIGHASH_ALL, 0, SIGVERSION_BASE);

    bytes vchSig;
    MUST_TRUE(sgx_seckey.Sign(sighash, vchSig));

    vchSig.push_back((unsigned char)SIGHASH_ALL);

    return CScript() << vchSig << ToByteVector(sgx_seckey.GetPubKey()) << branch
                     << ToByteVector(_redeemScript);
  }

public:
  Wallet(const vector<Party> &users, const Party &sgx)
      : _users(users), _sgx(sgx) {
    // use a relative_timeout of 10
    for (const auto &p : users) {
      lift_signals.emplace_back(p.GetPubKey(), 10);
    }

    auto n_user = EncodeOP_N(_users.size());

    _redeemScript << OP_IF;
    _redeemScript += _sgx.ScriptPubkey();
    _redeemScript << OP_ELSE << n_user;

    for (const auto &u : users) {
      _redeemScript << ToByteVector(u.GetPubKey());
    }

    _redeemScript << n_user << OP_CHECKMULTISIG << OP_ENDIF;

    _scriptPubKey = GetScriptForDestination(CScriptID(_redeemScript));
  }

  const CScript &scriptPubkey() const { return _scriptPubKey; }

  const CScript &redeemScript() const { return _redeemScript; }

  const CBitcoinAddress Address() const {
    return CBitcoinAddress(CScriptID(_redeemScript));
  }
};

#endif // PARALYSISPROOFS_PARALYSIS_H
