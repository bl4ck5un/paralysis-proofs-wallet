#include <algorithm>

#include "bitcoin/uint256.h"
#include "lest/lest.hpp"

#include "bitcoin/utilstrencodings.h"
#include "bitcoin_helpers.h"
#include "deposit.h"
#include "paralysis.h"

using namespace std;

const lest::test specification[] = {
    {CASE("generate new address") {
      const uint32_t cltvTimeout = 1547578486;
      CBitcoinSecret secret;
      secret.SetString("cURgah32X7tNqK9NCkpXVVd4bbocWm3UjgwyAGpdVfxicAZynLs5");
      auto script =
          generate_simple_cltv_script(secret.GetKey().GetPubKey(), cltvTimeout);
      auto addr = script_to_address(script);
          EXPECT(addr.ToString() == "2N7GnzMovd5tq1DpMQXDx6KfuGW2m6RbXpN");
    }
    }, {CASE("generate new address from complex scripts") {
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
    },

    {CASE("depositparam class") {
      const uint32_t cltvTimeout = 1000000;
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
    },

    {CASE("seckey") {
      CBitcoinSecret secret(secret_key_from_string_hash("exch"));
          EXPECT(secret.ToString() ==
          "cUCtr5hzrXKXsrpbZBM644kK1G7E3CzXdNPvDWYxt4FF7LxqZ9vz");

      secret.SetKey(secret_key_from_string_hash("alice"));
          EXPECT(secret.ToString() ==
          "cTvTf14w41TZMiKNyxiqCFLitgR7zZW1q8RHxMmMQXAcoQR4A966");
    }
    },

    {
        CASE("life signal") {
      auto user = Party("alice");
      LifeSignal ls(user.GetPubKey(), 10);
      auto sc = ls.GetRedeemScript();
    }
    }
};

#include "deposit.h"
#include "paralysis.h"

int enclaveTest() {
  //  test_settle_all();
  test_paralysis();

  SelectParams(CBaseChainParams::REGTEST);
  ECC_Start();
  lest::run(specification);
  ECC_Stop();
  return 0;
}