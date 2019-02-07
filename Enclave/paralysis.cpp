#include "paralysis.h"

#include "utils.h"

void test_paralysis() {
  SelectParams(CBaseChainParams::REGTEST);
  ECC_Start();

  try {

    vector<string> names = {"alice", "bob", "char", "david", "eve"};
    vector<Party> users;

    for (const auto &name : names) {
      LL_DEBUG("%s", name.c_str());
      users.emplace_back(name);
    }
    for (const auto &user : users) {
      LL_DEBUG("user: %s", user.ToString().c_str());
    }

    auto sgx = Party("sgx");
    LL_DEBUG("sgx: %s", sgx.ToString().c_str());

    Wallet wallet(users, sgx);
    LL_DEBUG("wallet redeemScript=%s",
             ScriptToAsmStr(wallet.redeemScript()).c_str());

    string dust_tx_hex =
        "020000000001023ae39b3324379dcb2258f42e6270155f8393e5d14976b8bc419f1875"
        "ff3b5d890100000017160014ed3947e5a8992aae50d06f7f4375857503791076fdffff"
        "ffb4fc5d489c3b238d98718b9a3ade94921f7cd4bf9a9e5962594e064fab626fa20200"
        "000017160014201b558498b581d9675074287f47482cbd228664fdffffff033c6ff405"
        "0000000017a914ebc8580e10c803ebe70d3fdd8ffb5ab2d8269a0b8750c30000000000"
        "001976a914567827d4bedca8a476fc0d6ab47dad54ad52379688ac00ca9a3b00000000"
        "17a91400593b17f9ff1e272c0086b46ec4161de2e89b4387024730440220371c07b294"
        "2339012aabfa70d6ae9bbe1d951db4d5e1952c5c1bd264e443432402201b7d5469eb02"
        "52735c64d3361215cd7849d4b38a8655de48d6e3463a8760519f01210387fb76f2352d"
        "fcc94ce2fe6b6a5af86c70a07cacd422c9362d99b5827a211b4a0247304402203a928b"
        "f0291936697bb9462f5c75431e2fcdb888e904df329aaf53e4942187480220331a0f23"
        "cc6055537a2287e34ae974d77705e02580ef4d467f5c82fa8b58789e01210234446fb0"
        "f7bc2b53ac063672e15da59a62f029770d83400b9fd5ada38f0fefa9ea000000";
    auto dust_op = OutPointWithTx(dust_tx_hex, sgx.ScriptPubkey());

    string wallet_deposit_tx_hex =
        "020000000001023ae39b3324379dcb2258f42e6270155f8393e5d14976b8bc419f1875"
        "ff3b5d890100000017160014ed3947e5a8992aae50d06f7f4375857503791076fdffff"
        "ffb4fc5d489c3b238d98718b9a3ade94921f7cd4bf9a9e5962594e064fab626fa20200"
        "000017160014201b558498b581d9675074287f47482cbd228664fdffffff033c6ff405"
        "0000000017a914ebc8580e10c803ebe70d3fdd8ffb5ab2d8269a0b8750c30000000000"
        "001976a914567827d4bedca8a476fc0d6ab47dad54ad52379688ac00ca9a3b00000000"
        "17a91400593b17f9ff1e272c0086b46ec4161de2e89b4387024730440220371c07b294"
        "2339012aabfa70d6ae9bbe1d951db4d5e1952c5c1bd264e443432402201b7d5469eb02"
        "52735c64d3361215cd7849d4b38a8655de48d6e3463a8760519f01210387fb76f2352d"
        "fcc94ce2fe6b6a5af86c70a07cacd422c9362d99b5827a211b4a0247304402203a928b"
        "f0291936697bb9462f5c75431e2fcdb888e904df329aaf53e4942187480220331a0f23"
        "cc6055537a2287e34ae974d77705e02580ef4d467f5c82fa8b58789e01210234446fb0"
        "f7bc2b53ac063672e15da59a62f029770d83400b9fd5ada38f0fefa9ea000000";
    auto wallet_op =
        OutPointWithTx(wallet_deposit_tx_hex, wallet.scriptPubkey());

    CFeeRate fixedRate(10000); // FIXME using a static 10000 Satoshi / KB
    LifeSignal ls(users[0].GetPubKey(), 10);

    LL_DEBUG("life signal script: %s",
             ScriptToAsmStr(ls.GetRedeemScript()).c_str());

    auto t = ls.into_transaction(sgx.GetSecret(), dust_op, fixedRate);
    LL_DEBUG("life signal (hex): %s", tx2hex(t).c_str());
  }
  CATCH_STD_AND_ALL_NO_RET

  ECC_Stop();
}
