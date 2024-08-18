
// 3.58

long decode2(long x, long y, long z) {
  y = y - z;
  x = x * y;

  return x ^ ((y << 63) >> 63);
}