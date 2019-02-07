#ifndef PARALYSISPROOFS_PARALYSIS_H
#define PARALYSISPROOFS_PARALYSIS_H

#include <string>

#include "bitcoin_helpers.h"

#include "bitcoin/pubkey.h"
#include "bitcoin/base58.h"
using std::string;
using std::move;

class Party {
 private:
  string _name;
  CPubKey pubkey;
  CBitcoinSecret secret;

 public:
  explicit Party(const string& name): _name(name), secret(secret_key_from_string_hash(_name)) {
    auto _pubkey = secret.GetKey().GetPubKey();
    pubkey.Set(_pubkey.begin(), _pubkey.end());
  }
  Party(string name, CPubKey pubkey): _name(move(name)), pubkey(pubkey.begin(), pubkey.end()) {}

  CBitcoinAddress Address() const {
    return CBitcoinAddress(pubkey.GetID());
  }

  CScript ScriptPubkey() const {
    return GetScriptForDestination(pubkey.GetID());
  }

  string ToString() const {
    return "name: " + _name + ", address=" + Address().ToString();
  }
};


class LifeSignal {
 private:
  CPubKey key1;
  CBitcoinSecret key2;
  uint32_t relative_timeout;
  CAmount amount;

  CScript _redeemScript;
  CScript _scriptPubkey;
 public:
  LifeSignal(const CPubKey& key1, uint32_t relative_timeout): key1(key1.begin(), key1.end()), key2(secret_key_from_string_hash("tmp secret")), relative_timeout(relative_timeout), amount(0.0001 * COIN) {
    _redeemScript << OP_IF << GetScriptForDestination(key1.GetID())
  }
};

#endif //PARALYSISPROOFS_PARALYSIS_H
