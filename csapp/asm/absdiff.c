/* gcc -O3 -S absdiff.c */

long absdiff(long x, long y) {
  long result;
  if (x < y) {
    result = y - x;
  } else {
    result = x - y;
  }
  return result;
}