#ifndef PARALYSIS_PROOF_UTILS_H
#define PARALYSIS_PROOF_UTILS_H

#include <stdlib.h>
#include <string>
#include <vector>

void byte_swap(unsigned char *data, int len);
void hd(const char *title, void const *data, size_t len);
std::string bin2hex(const unsigned char *bin, size_t len);
void hex2bin(unsigned char *dest, const char *src);
std::vector<unsigned char> hex2bin(const char *src);

#endif // PARALYSIS_PROOF_UTILS_H
