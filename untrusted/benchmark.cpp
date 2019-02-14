#include "benchmark.h"

void from_json(const json &j, Case &p) {
  j.at("size").get_to(p.n);
  j.at("wallet_tx").get_to(p.wallet_tx);
  j.at("fee_payment_tx").get_to(p.fee_payment_tx);
}
