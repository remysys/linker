/* gcc -Og -S muldiv.c */

#include <inttypes.h>
typedef unsigned __int128 uint128_t;

void store_uprod(uint128_t *dest, uint64_t x, uint64_t y) {
  *dest = x * (uint128_t) y;
}

void remdiv(long x, long y, long *qp, long *rp) {
  long q = x / y;
  long r = x % y;
  *qp = q;
  *rp = r;
}

void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp) {
  unsigned long q = x/y;
  unsigned long r = x%y;
  *qp = q;
  *rp = r;
}