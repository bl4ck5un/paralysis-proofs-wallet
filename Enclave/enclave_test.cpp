#include <algorithm>

#include "bitcoin/uint256.h"
#include "lest/lest.hpp"

#include "bitcoin/utilstrencodings.h"
#include "bitcoin_helpers.h"
#include "deposit.h"
#include "paralysis.h"

using namespace std;

const lest::test specification[] = {
    {CASE("generate new address"){const uint32_t cltvTimeout = 1547578486;
CBitcoinSecret secret;
secret.SetString("cURgah32X7tNqK9NCkpXVVd4bbocWm3UjgwyAGpdVfxicAZynLs5");
auto script =
    generate_simple_cltv_script(secret.GetKey().GetPubKey(), cltvTimeout);
auto addr = script_to_address(script);
EXPECT(addr.ToString() == "2N7GnzMovd5tq1DpMQXDx6KfuGW2m6RbXpN");
}
}
, {CASE("generate new address from complex scripts"){
      const uint32_t cltvTimeout = 1000000;
CBitcoinSecret user_secret, exch_secret;
user_secret.SetString("cTvTf14w41TZMiKNyxiqCFLitgR7zZW1q8RHxMmMQXAcoQR4A966");
exch_secret.SetString("cQWk83QU1v5kEDLznW12TLH6nqemmJ3T6bhKwgwfTawTGKeyRtFc");

auto script =
    generate_deposit_script(user_secret.GetKey().GetPubKey(),
                            exch_secret.GetKey().GetPubKey(), cltvTimeout);
auto addr = script_to_address(script);
EXPECT(addr.ToString() == "2NGFQnjaHX38fmS1di3MH8bf9Hd6NZxZTzv");
}
}
,

    {CASE("depositparam class"){const uint32_t cltvTimeout = 1000000;
CBitcoinSecret user_secret(secret_key_from_string_hash("alice")),
    exch_secret(secret_key_from_string_hash("exch"));
DepositParams params(user_secret.GetKey().GetPubKey(),
                     exch_secret.GetKey().GetPubKey(), cltvTimeout);
auto redeemScript = params.deposit_redeemScript();
EXPECT(params.address().ToString() == "2NAqCFC8FazvtUzGv23reB9kQyR9JBW48PB");

auto scriptPubkey = params.scriptPubkey();
EXPECT(HexStr(scriptPubkey.begin(), scriptPubkey.end()) ==
       "a914c0e6d37a01c9999d88b4dc252a39e571bea1603a87");
EXPECT(HexStr(redeemScript.begin(), redeemScript.end()) ==
       "6376a914966f83de4b1901794baec6a42322f8080db166cc88ac670340420fb17576a91"
       "46624a4de9b4973cba3b991bc26cd1c8f171a4e3d88ac68");
}
}
,

    {CASE("seckey"){CBitcoinSecret secret(secret_key_from_string_hash("exch"));
EXPECT(secret.ToString() ==
       "cUCtr5hzrXKXsrpbZBM644kK1G7E3CzXdNPvDWYxt4FF7LxqZ9vz");

secret.SetKey(secret_key_from_string_hash("alice"));
EXPECT(secret.ToString() ==
       "cTvTf14w41TZMiKNyxiqCFLitgR7zZW1q8RHxMmMQXAcoQR4A966");
}
}
,

{
  CASE("life signal") {
    auto user = Party("alice");
    LifeSignal ls(user.GetPubKey(), 10);
    auto sc = ls.GetRedeemScript();
  }
}
}
;

#include "deposit.h"
#include "paralysis.h"

void test_paralysis() {
  SelectParams(CBaseChainParams::REGTEST);
  ECC_Start();
  auto _ = std::unique_ptr<ECCVerifyHandle>(new ECCVerifyHandle());

  try {

    vector<string> names = {"alice", "bob", "char", "david", "eve"};
    vector<Party> users;

    for (const auto &name : names) {
      users.emplace_back(name);
    }
    for (const auto &user : users) {
      LL_DEBUG("user: %s", user.ToString().c_str());
    }

    auto sgx = Party("sgx");
    LL_DEBUG("sgx: %s", sgx.ToString().c_str());

    Wallet wallet(users, sgx, 10);
    LL_DEBUG("%s", wallet.ToString().c_str());

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

    CFeeRate fixed_rate(10000); // FIXME using a static 10000 Satoshi / KB

    auto tuple =
        wallet.accuse(dust_op, wallet_op, 0, sgx.GetSecret(), fixed_rate);
    LifeSignal ls = std::get<0>(tuple);
    CTransaction tx1 = std::get<1>(tuple);
    CTransaction tx2 = std::get<2>(tuple);

    auto life_signal_tx_hex = tx2hex(tx1);
    auto tx_appeal =
        wallet.appeal(0, users[0].GetSecret(),
                      OutPointWithTx(life_signal_tx_hex, ls.GetScriptPubKey()));

    LL_NOTICE("tx1 (hex): %s", tx2hex(tx1).c_str());
    LL_NOTICE("tx2 (hex): %s", tx2hex(tx2).c_str());
    LL_NOTICE("tx_appeal (hex): %s", tx2hex(tx_appeal).c_str());
  }
  CATCH_STD_AND_ALL_NO_RET

  ECC_Stop();
}

int enclaveTest() {
  //  test_settle_all();
  test_paralysis();

  SelectParams(CBaseChainParams::REGTEST);
  ECC_Start();
  lest::run(specification);
  ECC_Stop();
  return 0;
}