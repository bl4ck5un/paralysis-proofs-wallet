#include <algorithm>

#include "bitcoin/uint256.h"
#include "crypto_box.h"
#include "lest/lest.hpp"

#include "bitcoin/utilstrencodings.h"
#include "bitcoin_helpers.h"
#include "deposit.h"

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
}
;

#include "deposit.h"
#include "paralysis.h"

int enclaveTest() {
//  test_settle_all();

  SelectParams(CBaseChainParams::REGTEST);
  ECC_Start();
  lest::run(specification);


  vector<string> names = {"alice", "bob", "carol", "david", "eve"};
  vector<Party> users;

  for (auto name : names) {
    users.emplace_back(name);
  }

  for (const auto& user: users) {
    LL_DEBUG("user: %s", user.ToString().c_str());
  }

  auto sgx = Party("sgx");

  string dust_tx_hex = "020000000001023ae39b3324379dcb2258f42e6270155f8393e5d14976b8bc419f1875ff3b5d890100000017160014ed3947e5a8992aae50d06f7f4375857503791076fdffffffb4fc5d489c3b238d98718b9a3ade94921f7cd4bf9a9e5962594e064fab626fa20200000017160014201b558498b581d9675074287f47482cbd228664fdffffff033c6ff4050000000017a914ebc8580e10c803ebe70d3fdd8ffb5ab2d8269a0b8750c30000000000001976a914567827d4bedca8a476fc0d6ab47dad54ad52379688ac00ca9a3b0000000017a91400593b17f9ff1e272c0086b46ec4161de2e89b4387024730440220371c07b2942339012aabfa70d6ae9bbe1d951db4d5e1952c5c1bd264e443432402201b7d5469eb0252735c64d3361215cd7849d4b38a8655de48d6e3463a8760519f01210387fb76f2352dfcc94ce2fe6b6a5af86c70a07cacd422c9362d99b5827a211b4a0247304402203a928bf0291936697bb9462f5c75431e2fcdb888e904df329aaf53e4942187480220331a0f23cc6055537a2287e34ae974d77705e02580ef4d467f5c82fa8b58789e01210234446fb0f7bc2b53ac063672e15da59a62f029770d83400b9fd5ada38f0fefa9ea000000";
  auto dust_op = OutPointWithTx(dust_tx_hex, sgx.ScriptPubkey());

  string wallet_deposit_tx_hex = "020000000001023ae39b3324379dcb2258f42e6270155f8393e5d14976b8bc419f1875ff3b5d890100000017160014ed3947e5a8992aae50d06f7f4375857503791076fdffffffb4fc5d489c3b238d98718b9a3ade94921f7cd4bf9a9e5962594e064fab626fa20200000017160014201b558498b581d9675074287f47482cbd228664fdffffff033c6ff4050000000017a914ebc8580e10c803ebe70d3fdd8ffb5ab2d8269a0b8750c30000000000001976a914567827d4bedca8a476fc0d6ab47dad54ad52379688ac00ca9a3b0000000017a91400593b17f9ff1e272c0086b46ec4161de2e89b4387024730440220371c07b2942339012aabfa70d6ae9bbe1d951db4d5e1952c5c1bd264e443432402201b7d5469eb0252735c64d3361215cd7849d4b38a8655de48d6e3463a8760519f01210387fb76f2352dfcc94ce2fe6b6a5af86c70a07cacd422c9362d99b5827a211b4a0247304402203a928bf0291936697bb9462f5c75431e2fcdb888e904df329aaf53e4942187480220331a0f23cc6055537a2287e34ae974d77705e02580ef4d467f5c82fa8b58789e01210234446fb0f7bc2b53ac063672e15da59a62f029770d83400b9fd5ada38f0fefa9ea000000";
//  auto wallet_depo_op = OutPointWithTx(wallet_deposit_tx_hex, wallet.scriptPubkey)

  LL_DEBUG("dust: %s", dust_op.GetPrevOut().ToString().c_str());

  ECC_Stop();
  return 0;
}