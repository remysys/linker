/* gcc -Og -S exchange.c */

long exchange(long *xp, long y) {
  long x = *xp;
  *xp = y;
  return x;
}