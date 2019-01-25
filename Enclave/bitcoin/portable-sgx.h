#ifndef PARALYSIS_PROOF_BITCOIN_SGX_H
#define PARALYSIS_PROOF_BITCOIN_SGX_H

static std::string strprintf(const char* fmt, ...) {
  va_list ap;
  constexpr size_t BUFSIZE = 512;
  char buf[BUFSIZE] = {'\0'};
  va_start(ap, fmt);
  vsnprintf(buf, BUFSIZE, fmt, ap);
  va_end(ap);

  return std::string(buf);
}
#endif //PARALYSIS_PROOF_SGX_H
