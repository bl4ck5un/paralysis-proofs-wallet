#include <algorithm>

#include "bitcoin/uint256.h"

#include "bitcoin/utilstrencodings.h"
#include "bitcoin_helpers.h"
#include "paralysis.h"

using namespace std;

int parse_wallet_info(const char *_redeemScript, const char *_walletUtxoTx) {
  try {
    auto _rs_binary = ParseHex(_redeemScript);
    CScript redeemScript(_rs_binary.begin(), _rs_binary.end());

    LL_DEBUG("redeemScript: %s", ScriptToAsmStr(redeemScript).c_str());
    LL_DEBUG(
        "redeemScript -> pubkey: %s",
        ScriptToStr(GetScriptForDestination(CScriptID(redeemScript))).c_str());

    auto walletUtxoTx = OutPointWithTx(
        _walletUtxoTx, GetScriptForDestination(CScriptID(redeemScript)));

    LL_NOTICE("here");

    return 0;
  }
  CATCH_STD_AND_ALL
}

#include "bitcoin/chainparamsbase.h"

class ECCContext {
private:
  ECCVerifyHandle *ecc_handle;

public:
  ECCContext() {
    SelectParams(CBaseChainParams::REGTEST);

    ECC_Start();
    ecc_handle = new ECCVerifyHandle();
  }
  ~ECCContext() {
    ECC_Stop();
    delete ecc_handle;
  }
};

std::unique_ptr<ECCContext> ctx;

#include "message.h"

Party defaultManager() { return Party("sgx"); }

vector<Party> defaultUsers() {
  vector<string> names = {"alice", "bob", "char", "david", "eve"};
  vector<Party> users;

  for (const auto &name : names) {
    users.emplace_back(name);
  }

  return users;
}

Wallet defaultWallet() {
  auto users = defaultUsers();
  auto sgx = defaultManager();

  // FIXME using a fixed expiration time (144 blocks = 24 hours)
  Wallet wallet(users, sgx, 144);

  return wallet;
}

int accuse(const char *_feePaymentTx, const char *_walletUtxoTx,
           size_t who_to_accuse, AccusationResult *result) {
  if (!ctx) {
    ctx = std::unique_ptr<ECCContext>(new ECCContext());
  }
  try {
    auto wallet = defaultWallet();
    auto sgx = defaultManager();

    LL_DEBUG("%s", wallet.ToString().c_str());
    LL_DEBUG("wallet redeemScript: %s",
             ScriptToStr(wallet.redeemScript()).c_str());
    LL_DEBUG("wallet scriptPubKey: %s",
             ScriptToStr(wallet.scriptPubkey()).c_str());

    auto dust_op = OutPointWithTx(string(_feePaymentTx), sgx.ScriptPubkey());
    auto wallet_op =
        OutPointWithTx(string(_walletUtxoTx), wallet.scriptPubkey());

    CFeeRate fixed_rate(10000); // FIXME using a static 10000 Satoshi / KB

    auto tuple = wallet.accuse(dust_op, wallet_op, who_to_accuse,
                               sgx.GetSecret(), fixed_rate);
    CTransaction tx1 = std::get<0>(tuple);
    CTransaction tx2 = std::get<1>(tuple);

    auto size = tx2arbuf(result->tx1, tx1);
    result->tx1_len = size;

    size = tx2arbuf(result->tx2, tx2);
    result->tx2_len = size;

    return 0;
  }
  CATCH_STD_AND_ALL
}

int appeal(const char *life_signal_tx, size_t who_to_accuse,
           AppealResult *result) {
  if (!ctx) {
    ctx = std::unique_ptr<ECCContext>(new ECCContext());
  }

  try {
    auto wallet = defaultWallet();
    auto users = defaultUsers();

    // appeal to a life signal
    auto ls = wallet.GetLifeSignals().at(who_to_accuse);
    auto user = users.at(who_to_accuse);

    auto tx_appeal =
        wallet.appeal(who_to_accuse, user.GetSecret(),
                      OutPointWithTx(life_signal_tx, ls.GetScriptPubKey()));

    auto size = tx2arbuf(result->tx, tx_appeal);
    result->len = size;

    return 0;
  }
  CATCH_STD_AND_ALL
}

void test_paralysis() {
  if (!ctx) {
    ctx = std::unique_ptr<ECCContext>(new ECCContext());
  }

  try {
    vector<string> names = {"alice", "bob", "char", "david", "eve"};
    vector<Party> users;

    for (const auto &name : names) {
      users.emplace_back(name);
    }

    Party sgx("sgx");

    Wallet wallet(users, sgx, 144);
    LL_NOTICE("%s", wallet.ToString().c_str());
    LL_LOG("wallet redeemScript: %s",
           ScriptToStr(wallet.redeemScript()).c_str());
    LL_LOG("wallet scriptPubKey: %s",
           ScriptToStr(wallet.scriptPubkey()).c_str());

    string dust_tx_hex =
        "020000000001017dbab870699def97d4d8453e94f256bfc8505941768c37f1dcea0563"
        "3ade94480100000017160014f52f687441761fe267c60d324141580189e6461efdffff"
        "ff0350c30000000000001976a914567827d4bedca8a476fc0d6ab47dad54ad52379688"
        "ac7cbdcb1d0000000017a91492f4aeefd6fca1219a6684a46dca2abd66b0fbcc8700ca"
        "9a3b0000000017a91400593b17f9ff1e272c0086b46ec4161de2e89b43870247304402"
        "203314792420e909460ff19117440546f9b1ba5a7d9f4b6e57de4646005cede2b10220"
        "78989d4e7abcda79001fd2dc1ca9745ffb8e066a1a1bfdd35a51681d13c4d64d012103"
        "397eaed8ed2c889b1dbc99d6a97ea5d39e185d0b614fa88074449666564fccb0e40000"
        "00";
    auto dust_op = OutPointWithTx(dust_tx_hex, sgx.ScriptPubkey());

    string wallet_deposit_tx_hex =
        "020000000001017dbab870699def97d4d8453e94f256bfc8505941768c37f1dcea0563"
        "3ade94480100000017160014f52f687441761fe267c60d324141580189e6461efdffff"
        "ff0350c30000000000001976a914567827d4bedca8a476fc0d6ab47dad54ad52379688"
        "ac7cbdcb1d0000000017a91492f4aeefd6fca1219a6684a46dca2abd66b0fbcc8700ca"
        "9a3b0000000017a91400593b17f9ff1e272c0086b46ec4161de2e89b43870247304402"
        "203314792420e909460ff19117440546f9b1ba5a7d9f4b6e57de4646005cede2b10220"
        "78989d4e7abcda79001fd2dc1ca9745ffb8e066a1a1bfdd35a51681d13c4d64d012103"
        "397eaed8ed2c889b1dbc99d6a97ea5d39e185d0b614fa88074449666564fccb0e40000"
        "00";
    auto wallet_op =
        OutPointWithTx(wallet_deposit_tx_hex, wallet.scriptPubkey());

    LL_DEBUG("dust tx (hex): %s", dust_tx_hex.c_str());
    LL_DEBUG("wallet tx (hex): %s", wallet_deposit_tx_hex.c_str());

    auto accusation_result = accusation_result_init();
    auto appeal_result = appeal_result_init();

    MUST_TRUE(0 == accuse(dust_tx_hex.c_str(), wallet_deposit_tx_hex.c_str(), 0,
                          &accusation_result));

    LL_NOTICE("tx1 (hex): %s",
              HexStr(accusation_result.tx1,
                     accusation_result.tx1 + accusation_result.tx1_len)
                  .c_str());
    LL_NOTICE("tx2 (hex): %s",
              HexStr(accusation_result.tx2,
                     accusation_result.tx2 + accusation_result.tx2_len)
                  .c_str());
    LL_NOTICE(
        "tx_appeal (hex): %s",
        HexStr(appeal_result.tx, appeal_result.tx + appeal_result.len).c_str());
  }
  CATCH_STD_AND_ALL_NO_RET
}

int enclaveTest() {
  test_paralysis();

  return 0;
}