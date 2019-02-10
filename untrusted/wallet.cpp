#include "wallet.h"

void from_json(const json &j, User &p) {
  j.at("name").get_to(p.name);
  j.at("pubkey").get_to(p.pubkey);
}
