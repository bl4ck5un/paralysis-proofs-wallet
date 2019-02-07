#include "pprint.h"
#include "utils.h"

void hexdump(const char *title, void const *data, size_t len) {
  unsigned int i;
  unsigned int r, c;

  if (!data)
    return;

  printf_std("%s\n", title);

  for (r = 0, i = 0; r < (len / 16 + (len % 16 != 0)); r++, i += 16) {
    printf_std("0x%04X:   ", i); /* location of first byte in line */

    for (c = i; c < i + 8; c++) /* left half of hex dump */
      if (c < len)
        printf_std("%02X ", ((unsigned char const *)data)[c]);
      else
        printf_std("   "); /* pad if short line */

    printf_std("  ");

    for (c = i + 8; c < i + 16; c++) /* right half of hex dump */
      if (c < len)
        printf_std("%02X ", ((unsigned char const *)data)[c]);
      else
        printf_std("   "); /* pad if short line */

    printf_std("   ");

    for (c = i; c < i + 16; c++) /* ASCII dump */
      if (c < len)
        if (((unsigned char const *)data)[c] >= 32 &&
            ((unsigned char const *)data)[c] < 127)
          printf_std("%c", ((char const *)data)[c]);
        else
          printf_std("."); /* put this for non-printables */
      else
        printf_std(" "); /* pad if short line */

    printf_std("\n");
  }
}