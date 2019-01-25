#include <algorithm>

#include "lest/lest.hpp"
#include "bitcoin/uint256.h"
#include "crypto_box.h"
#include "securechannel.h"

#include "bitcoin_helpers.h"
#include "bitcoin/utilstrencodings.h"
#include "deposit.h"

using namespace std;

const lest::test specification[] =
    {
        {CASE("generate new address") {
          const uint32_t cltvTimeout = 1547578486;
          CBitcoinSecret secret;
          secret.SetString("cURgah32X7tNqK9NCkpXVVd4bbocWm3UjgwyAGpdVfxicAZynLs5");
          auto script = generate_simple_cltv_script(secret.GetKey().GetPubKey(), cltvTimeout);
          auto addr = create_p2sh_address(script);
              EXPECT(addr.ToString() == "2N7GnzMovd5tq1DpMQXDx6KfuGW2m6RbXpN");
        }},
        {CASE("generate new address from complex scripts") {
          const uint32_t cltvTimeout = 1000000;
          CBitcoinSecret user_secret, exch_secret;
          user_secret.SetString("cTvTf14w41TZMiKNyxiqCFLitgR7zZW1q8RHxMmMQXAcoQR4A966");
          exch_secret.SetString("cQWk83QU1v5kEDLznW12TLH6nqemmJ3T6bhKwgwfTawTGKeyRtFc");

          auto script =
              generate_deposit_script(user_secret.GetKey().GetPubKey(), exch_secret.GetKey().GetPubKey(), cltvTimeout);
          auto addr = create_p2sh_address(script);
              EXPECT(addr.ToString() == "2NGFQnjaHX38fmS1di3MH8bf9Hd6NZxZTzv");
        }},

        {CASE("depositparam class") {
          const uint32_t cltvTimeout = 1000000;
          CBitcoinSecret user_secret(seckey_from_str("alice")), exch_secret(seckey_from_str("exch"));
          DepositParams params(user_secret.GetKey().GetPubKey(), exch_secret.GetKey().GetPubKey(), cltvTimeout);
          auto redeemScript = params.deposit_redeemScript();
          EXPECT(params.address().ToString() == "2NAqCFC8FazvtUzGv23reB9kQyR9JBW48PB");

          auto scriptPubkey = params.scriptPubkey();
          EXPECT(HexStr(scriptPubkey.begin(), scriptPubkey.end()) == "a914c0e6d37a01c9999d88b4dc252a39e571bea1603a87");
          EXPECT(HexStr(redeemScript.begin(), redeemScript.end()) == "6376a914966f83de4b1901794baec6a42322f8080db166cc88ac670340420fb17576a9146624a4de9b4973cba3b991bc26cd1c8f171a4e3d88ac68");
        }},

        {CASE("seckey"){
          CBitcoinSecret secret(seckey_from_str("exch"));
          EXPECT(secret.ToString() == "cUCtr5hzrXKXsrpbZBM644kK1G7E3CzXdNPvDWYxt4FF7LxqZ9vz");

          secret.SetKey(seckey_from_str("alice"));
          EXPECT(secret.ToString() == "cTvTf14w41TZMiKNyxiqCFLitgR7zZW1q8RHxMmMQXAcoQR4A966");
        }},
    };

int test_securechannel() {
  using namespace exch::enclave::securechannel;

  string skA;
  string pkA = nacl_crypto_box_keypair(&skA);

  string skB;
  string pkB = nacl_crypto_box_keypair(&skB);

  string msg{1, 2, 3, 4, 5};

  Peer peerA("localhost", 1234, pkA, skA);
  Peer peerB("localhost", 4321, pkB, skB);

  try {
    for (auto i = 0; i < 10; i++) {
      Box boxAtoB = peerA.createBoxToPeer(peerB, msg);
      string msgB = peerB.openBoxFromPeer(boxAtoB, peerA);
      hexdump("B received:", msgB.data(), msgB.size());
    }
  }
  catch (const exception &e) {
    LL_CRITICAL("%s", e.what());
  }
  return 0;
}

using namespace exch::enclave;

#include "deposit.h"

extern bool test_simple_cltv_redeem();
int enclaveTest() {
//  test_simple_cltv_redeem();
//  test_settlement();
  test_settle_all();
  SelectParams(CBaseChainParams::REGTEST);
  ECC_Start();
  lest::run(specification);
  ECC_Stop();
  return 0;
}