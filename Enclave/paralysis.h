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
using std::vector;

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
        relative_timeout(relative_timeout), amount(10000) {
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
    auto branch = OP_TRUE;
    auto sighash = SignatureHash(_redeemScript, unsigned_tx, which_to_sign,
                                 SIGHASH_ALL, 0, SIGVERSION_BASE);

    std::vector<unsigned char> vchSig;
    secret.Sign(sighash, vchSig);
    vchSig.push_back((unsigned char)SIGHASH_ALL);

    auto sc = CScript();

    sc << vchSig;
    sc << ToByteVector(secret.GetPubKey());
    sc << branch;
    sc << ToByteVector(_redeemScript);

    return sc;
  }

  const CScript scriptSigByKey2(const CMutableTransaction &unsigned_tx,
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
    LL_DEBUG("sum_in: %d", sum_in);

    auto fees = fee_rate.GetFee(tx_size(1, 2));
    auto refund = sum_in - fees - this->amount;

    LL_DEBUG("fee: %d", fees);
    LL_DEBUG("refund: %d", refund);

    MUST_TRUE(refund >= 0);

    CMutableTransaction unsigned_tx;
    unsigned_tx.vin.emplace_back(dust_op.GetOutPoint());
    unsigned_tx.vout.emplace_back(amount, _scriptPubkey);
    unsigned_tx.vout.emplace_back(
        refund, GetScriptForDestination(dust_seckey.GetPubKey().GetID()));

    // spend the dust input
    CBasicKeyStore tmp;
    tmp.AddKey(dust_seckey);
    if (!SignSignature(tmp, dust_op.GetPrevOut().scriptPubKey, unsigned_tx, 0,
                       0, SIGHASH_ALL)) {
      throw std::runtime_error("can't sign the dust input");
    }

    LL_DEBUG("done signing");
    return CTransaction(unsigned_tx);
  }

  // this always return zero, because the life signal is always the first output
  const static size_t nOutForLifeSignalOutput;
};

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

  CScript sigScriptBySGX(const CKey &sgx_seckey,
                         const CMutableTransaction &unsigned_tx,
                         uint32_t which_to_sign) {
    auto branch = OP_TRUE;
    auto sighash = SignatureHash(redeemScript(), unsigned_tx, which_to_sign,
                                 SIGHASH_ALL, 0, SIGVERSION_BASE);

    bytes vchSig;
    MUST_TRUE(sgx_seckey.Sign(sighash, vchSig));

    vchSig.push_back((unsigned char)SIGHASH_ALL);

    return CScript() << vchSig << ToByteVector(sgx_seckey.GetPubKey()) << branch
                     << ToByteVector(redeemScript());
  }

public:
  Wallet(const vector<Party> &users, const Party &sgx,
         uint32_t life_signal_span)
      : _users(users), _sgx(sgx) {
    // use a relative_timeout of 10
    for (const auto &p : users) {
      lift_signals.emplace_back(p.GetPubKey(), life_signal_span);
    }
  }
  const CScript
  redeemScript(const vector<size_t> &excluded_indices = {}) const {
    vector<Party> current_users;
    for (size_t i = 0; i < _users.size(); i++) {
      // if i is not in excluded_indices
      if (std::find(excluded_indices.begin(), excluded_indices.end(), i) ==
          excluded_indices.end()) {
        current_users.push_back(_users[i]);
      }
    }

    auto N_USER = EncodeOP_N(current_users.size());

    CScript sc;
    sc << OP_IF;
    sc += _sgx.ScriptPubkey();
    sc << OP_ELSE << N_USER;

    for (const auto &u : current_users) {
      sc << ToByteVector(u.GetPubKey());
    }

    sc << N_USER << OP_CHECKMULTISIG << OP_ENDIF;

    return sc;
  }

  const CScript
  scriptPubkey(const vector<size_t> &excluded_indices = {}) const {
    return GetScriptForDestination(CScriptID(redeemScript(excluded_indices)));
  }

  const CBitcoinAddress Address() const {
    return CBitcoinAddress(CScriptID(redeemScript()));
  }

#include <stdio.h>

  string ToString() const {
    string info;
    info += "TEE manager: " + _sgx.ToString() + "\n";
    info += "Currently serving " + std::to_string(_users.size()) + " users\n";
    for (const auto &user : _users) {
      info += user.ToString() + "\n";
    }

    info += "address=" + Address().ToString();
    return info;
  }

  CTransaction appeal(size_t user_index, const CKey &user_secret,
                      const OutPointWithTx &life_signal_op) {
    auto ls = this->lift_signals[user_index];

    if (life_signal_op.GetPrevOut().scriptPubKey != ls.GetScriptPubKey()) {
      throw std::invalid_argument("mismatch scriptPubkey");
    }

    CMutableTransaction unsigned_tx;
    unsigned_tx.vin.emplace_back(life_signal_op.GetOutPoint());
    unsigned_tx.vout.emplace_back(0, CScript() << OP_TRUE);

    LL_DEBUG("done creating tx");
    auto sig = ls.scriptSigByKey1(user_secret, unsigned_tx, 0);
    unsigned_tx.vin[0].scriptSig = sig;

    LL_DEBUG("done signing");

    return CTransaction(unsigned_tx);
  }

  std::tuple<LifeSignal, CTransaction, CTransaction>
  accuse(const OutPointWithTx &dust_op, const OutPointWithTx &wallet_op,
         size_t user_index, const CKey &sgx_seckey, const CFeeRate &fee_rate) {
    auto ls_tx = this->lift_signals[user_index].into_transaction(
        sgx_seckey, dust_op, fee_rate);
    auto ls = this->lift_signals[user_index];

    if (wallet_op.GetPrevOut().scriptPubKey != this->scriptPubkey()) {
      LL_CRITICAL("wallet scriptPubkey: %s",
                  ScriptToAsmStr(wallet_op.GetPrevOut().scriptPubKey).c_str());
      throw std::invalid_argument("wallet uxto can't be spent");
    }

    CMutableTransaction unsigned_tx;
    unsigned_tx.nVersion = CTransaction::CURRENT_VERSION;

    // populate the life signal transaction and wallet outpoint
    unsigned_tx.vin.emplace_back(ls_tx.GetHash(),
                                 LifeSignal::nOutForLifeSignalOutput, CScript(),
                                 ls.GetRelativeTimeout());
    unsigned_tx.vin.emplace_back(wallet_op.GetOutPoint());

    // populate the output
    unsigned_tx.vout.emplace_back(wallet_op.GetPrevOut().nValue,
                                  this->scriptPubkey({user_index}));

    // sign
    auto lifesignal_sigScript = ls.scriptSigByKey2(unsigned_tx, 0);
    auto wallet_sigScript = this->sigScriptBySGX(sgx_seckey, unsigned_tx, 1);

    unsigned_tx.vin[0].scriptSig = lifesignal_sigScript;
    unsigned_tx.vin[1].scriptSig = wallet_sigScript;

    LL_DEBUG("done signing");

    CTransaction tx2(unsigned_tx);

    return std::make_tuple(ls, ls_tx, tx2);
  }
};

#endif // PARALYSISPROOFS_PARALYSIS_H
