#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <math.h>

// 2.57
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++)
    printf(" 0x%.2x", start[i]);
  printf("\n");
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int)); 
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
  show_bytes((byte_pointer) &x, sizeof(void *));
}

void show_short(short x) {
  show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x) {
  show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(long x) {
  show_bytes((byte_pointer) &x, sizeof(double));
}


void test_show_bytes(int val) {
  int ival = val;
  float fval = (float) ival;
  int *pval = &ival;

  short sval = (short) val;
  long lval = (long) val;
  double dval = (double) val;

  show_int(ival);
  show_float(fval);
  show_pointer(pval);
  show_short(sval);
  show_long(lval);
  show_double(dval);
}

// 2.58
int is_little_endian() {
  int val = 0xff;
  unsigned char *p = (unsigned char *) &val;

  return p[0] == 0xff;
}

// 2.59
unsigned int gen_word(unsigned int x, unsigned int y) {
  int mask = 0xff;
  return (x & mask) | (y & ~mask);
}

// 2.60
unsigned replace_byte(unsigned x, int i, unsigned char b) {
  unsigned int mask = 0xFF << (i << 3);
  unsigned int val = b << (i << 3);

  return (x & ~mask) | val;
}

// 2.61

/* any bit of x equals 1 */
int A(int x) {
  return !~x;
}

int B(int x) {
  return !x;
}

int C(int x) {
  return !~(x | ~0xff);
}

int D(int x) {
  return !(x >> ((sizeof(int) - 1) << 3));
}

// 2.62

int int_shifts_are_arithmetic() {
  int val = -1;

  return !(val ^ (val >> 1));
}

// 2.63

/*  logical right shift  */
unsigned srl(unsigned x, int k) {
  /* perform shift arithmetically */
  unsigned xsra = (int) x >> k;

  int w = sizeof(int) << 3;
  int mask = (int) -1 << (w - k);
  return xsra & ~mask;
}

/* arithmetic right shift */
int sra(int x, int k) {
  /* perform shift logically */
  int xsrl = (unsigned) x >> k;

  int w = sizeof(int) << 3;
  int mask = (int) -1 << (w - k);
  int m = (int) -1 << (w - 1);
  mask &= !(x & m) - 1;
  return xsrl | mask;
}

// 2.64
/* return 1 when any odd bit of x equals 1; 0 otherwise. assume w=32 */
int any_odd_one(unsigned x) {
  unsigned mask = 0xAAAAAAAA;
  return !!(x & mask);
}

// 2.65
/* return 1 when x contains an odd number of 1s; 0 otherwise. assume w=32 */
int odd_ones(unsigned x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  x &= 0x1;
  return x;
}

// 2.66
/*
 * generate mask indicating leftmost 1 in x. assume w=32.
 * for example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * if x = 0, then return 0.
 */
int leftmost_one(unsigned x) {
  /*
   * first, generate a mask that all bits after leftmost one are one
   * e.g. 0xFF00 -> 0xFFFF, and 0x6000 -> 0x7FFF
   * if x = 0, get 0
   */

  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  /*
   * then, do (mask >> 1) + (mask && 1), in which mask && 1 deals with case x = 0, 
   * reserve leftmost bit one that's we want
   */
  return (x >> 1) + (x && 1);
}

// 2.67

int int_size_is_32() {
  int set_msb = 1 << 31;
  int beyond_msb = set_msb << 1;

  return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bit() {
  int set_msb = 1 << 15 << 15 << 1;
  int beyond_msb = set_msb << 1;

  return set_msb && !beyond_msb;
}

// 2.68

int lower_one_mask(int n) {
  int w = sizeof(int) << 3;
  return ((unsigned int) -1) >> (w - n);
}

// 2.69

/*
* do rotating left shift. assume 0 <=n<w
* examples when x = 0x12345678 and w = 32:
* n=4 -> 0x23456781, n=20 -> 0x67812345
*/

unsigned rotate_left(unsigned x, int n) {
  int w = sizeof(int) << 3;
  /* pay attention when n == 0 */
  return (x << n) | (x >> (w - n - 1) >> 1);
}

// 2.70 
/*
* return 1 when x can be represented as an n-bit, 2’s-complement
* number; 0 otherwise
* assume 1 <= n <= w
*/

int fits_bits(int x, int n) {
  int w = sizeof(int) << 3;
  int offset = w - n;
  /* the point is x << (w-n) >> (w-n) must be equal to x itself */
  return ((x << offset) >> offset) == x;
}

// 2.71

/* extract byte from word. return as signed integer */
typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
  int w = sizeof(packed_t);

  int left =(w - bytenum - 1) << 3;
  int right = (w - 1) << 3;

  return ((int) word) << left >> right;
}

// 2.72
void copy_int(int val, void *buf, int maxbytes) {
  if (maxbytes >= (int) sizeof(val)) {
    memcpy(buf, (void *) &val, sizeof(val));
  }
}

// 2.73

/* addition that saturates to TMin or TMax */
int saturating_add(int x, int y) {
  int sum = x + y;
  int mask = INT_MIN;
  /*
   * if x > 0, y > 0 but sum < 0, it's a positive overflow
   * if x < 0, y < 0 but sum >= 0, it's a negetive overflow
   */

  int pos_overflow = !(x & mask) && !(y & mask) && (sum & mask);
  int neg_overflow = (x & mask) && (y & mask) && !(sum & mask);

  ((pos_overflow && (sum = INT_MAX)) || (neg_overflow && (sum = INT_MIN)));

  return sum;
}

// 2.74

/* 
 * determine whether arguments can be subtracted without overflow 
 * this function should return 1 if the computation x-y does not overflow
 */

int tsub_ok(int x, int y) {
  
  int sub = x - y;
  
  int overflow = 0;
  (y == INT_MIN && x == 0) && (overflow = 1);

  /*
   * if x > 0, y < 0 but sub < 0, it's a positive overflow
   * if x < 0, y > 0 but sub >= 0, it's a negetive overflow
   */

  int pos_overflow = (x > 0) && (y < 0) && sub < 0;
  int neg_overflow = (x < 0) && (y > 0) && sub >= 0;

  return !(pos_overflow || neg_overflow || overflow);
}

// 2.75

int signed_high_prod(int x, int y) {
  int64_t mul = (int64_t) x * y;
  return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
   /*
    *  ux: unsigned x
    *  uy: unsigned y
    *  x: signed x
    *  y: signed y
    *  m: w - 1 bit of x
    *  n: w - 1 bit of y
    *  ux = x + m*2^w
    *  uy = y + n*2^w
    *  a = m*2^w
    *  b = n*2^w
    *  ux * uy = (x + a) * (y + b) = x*y + x*b + y*a + a*b;
    *  hi32: get high 32 bit
    *  hi32(ux * uy) = hi32(x*y) + hi32(x*b) + hi32(y*a) + hi32(a*b)
    *  hi32(x*y) is signed_high_prod(x, y);
    *  hi32(x*b) = hi32(x*n*2^w) = x*n
    *  hi32(y*a) = hi32(y*m*2^w) = y*m
    *  hi32(a*b) = hi32(m*n*2^w*2w) = 0;
    */ 

    return signed_high_prod(x, y) + (int) x * (y >> 31) + (int) y * (x >> 31);
}

/* for test */
unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
  uint64_t mul = (uint64_t) x * y;
  return mul >> 32;
}

// 2.76

/* rename to avoid conflict */
void *another_calloc(size_t nmemb, size_t size) {
  size_t buf_size = nmemb * size;
  /* check overflow */
  if (!size || buf_size / size == nmemb) {
    if (buf_size == 0) {
      return NULL;
    }

    void *ptr = malloc(buf_size);
    if (!ptr) {
      memset(ptr, 0, buf_size);
    }
    return ptr;
  }

  return NULL;
}

// 2.77

/* k = 17 */
int Amul(int x) {
  return (x << 4) + x;
}

/* k = -7 */
int Bmul(int x) {
  return x - (x << 3);
}

/* k = 60 */
int Cmul(int x) {
  return (x << 6) - (x << 2);
}

/* k = -112 */
int Dmul(int x) {
  return (x << 4) - (x << 7);
}

// 2.78

/* divide by power of 2. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
  /* (x<0 ? x+(1<<k)-1 : x) >> k */

  return ((x & INT_MIN) ? x + (1 << k) - 1 : x) >> k;
}

// 2.79

int mul3div4(int x) {
  /* mul 3 */
  x = (x << 1) + x;
  
  /* div 4 */
  return ((x & INT_MIN) ? x + (1 << 2) - 1 : x) >> 2;
}

// 2.80
/* (3x)/4 */
int threefourths(int x) {
  /* 
   * no overflow means divide 4 first, then multiple 3, 
   * diffrent from 2.79 here
   */

  
  /* 
   * f = x & ~0x3
   * l = x & 0x3
   * x = f + l
   * 
   * x = (x << 1) + x 
   * equals:
   * f = (f << l) + f    (1)
   * l = (l << 1) + l
   * 
   * if x >= 0
   * x >> 2 equals: 
   * (f >> 2) + (l >> 2)
   * 
   * if x < 0
   * equals:
   * (x + bias) >> 2 equals:
   * ((f + l) + bias) >> 2
   * (f + (l + bias)) >> 2;
   * (f >> 2) + (l + bias) >> 2 
   * 
   * (1) may overflow and f is a multiple of 4
   * for f: divide 4 first, then multiple 3
   * 
   */
   
  int l = x & 0x3;
  int f = x & ~0x3;

  /* f divide 4 first, then multiple 3 */
  f = f >> 2;   
  f = (f << 1) + f;
  
  /* l multiple 3 first, then divide 4 */
  l = (l << 1) + l;
  int bias = (1 << 2) - 1;

  l = ((x & INT_MIN) ? l + bias : l) >> 2;
  
  return f + l;
}

// 2.81 
int genA(int k) {
  /* (w-k) 1s followed by k 0s */
  return -1 << k;
}

int genB(int k, int j) {
  /* (w-k-j) 0s k 1s j 0s */
  int w = sizeof(int) << 3;
  
  return ((unsigned int) -1 >> (w - k)) << j;
}

// 2.84

unsigned f2u(float x) {
  return *(unsigned *)&x;
}

int float_le(float x, float y) {
  unsigned ux = f2u(x);
  unsigned uy = f2u(y);

  unsigned sx = ux >> 31;
  unsigned sy = uy >> 31;

  /* 
   * sx == sy: 
   * sx == 0 => return ux <= uy
   * sx != 0 => return ux >= uy
   *  
   * sx != sy:
   * sx = 0 and sy = 1 => return sx > sy
   * sx = 1 and sy = 0 => return sx > sy
   */
 
  return sx == sy ? (sx == 0 ? ux <= uy : ux >= uy) : sx > sy;
}

// 2.89
/* (float) x == (float) dx : true */
int fA(int x, double dx) {
  return (float)x == (float)dx;
}

/* dx - dy == (double) (x-y) : false when y == INT_MIN */
int fB(int x, double dx, int y, double dy) {
  // printf("x: %d dx: %lf y: %d dy: %lf\n", x, dx, y, dy);
  // printf("dx-dy: %lf (double)(x - y): %lf\n", dx - dy, (double)(x - y));
  return dx - dy == (double)(x - y);
}

/* (dx + dy) + dz == dx + (dy + dz): false 
 * floating-point addition is not associative
 * FIXME I don't know what conditions cause false
 */

int fC(double dx, double dy, double dz) {
  // printf("dx: %lf\n", dx);
  // printf("(dx + dy) + dz: %lf \n dx + (dy + dz): %f\n", (dx + dy) + dz, dx + (dy + dz));
  return (dx + dy) + dz == dx + (dy + dz);
}

/* (dx * dy) * dz == dx * (dy * dz): false 
 * floating-point multiplication is not commutative
 * FIXME I don't know what conditions cause false
 */
int fD(double dx, double dy, double dz) {
  return (dx * dy) * dz == dx * (dy * dz);
}

/* dx / dx == dz / dz 
 * wrong when dx != 0 and dz == 0 
 */
int fE(double dx, double dz) {
  return dx / dx == dz / dz;
}

// 2.90

float u2f(unsigned int x) {
  return *(float *)&x;
}

/* 2^x */
float fpwr2(int x) {
  /* result exponent and fraction */
  unsigned exp, frac;
  unsigned u;
  if (x < -149) { /* 2^-149 is smallest denormalized */
    /* too small. return 0.0 */
    exp = 0;
    frac = 0;
  } else if (x < -126) { /* (1 * 2^−126 smallest normalized */
    /* 
     * denormalized result 
     * V = M * 2^E = 2^x
     * frac = M = 2^(x - E)
     * E = 1 - bias = -126;
     * 0 00000000 0...1 == 2^-23
     * frac = 1 << (x - E - (-23))
     * frac = 1 << (x + 149);
     */

    exp = 0;
    frac = 1 << (x + 149);
  } else if (x < 128) {
    /* normalized result. 
     * V = M * 2^E = 2^x
     * M = 1 = 1 + frac 
     * => frac = 0
     * E = x
     * E = exp - bias = x
     * exp = x + bias = x + (2^7 - 1) 
     */

    exp = x + 127;
    frac = 0;
  } else {
    /* too big. Return +oo */
    exp = 0xff;
    frac = 0;
  }

  /* pack exp and frac into 32 bits */
  u = exp << 23 | frac;
  /* return as float */
  return u2f(u);
}

// 2.91

/* access bit-level representation floating-point number */
typedef unsigned float_bits;

/* compute -f. If f is NaN, then return f. */
float_bits float_negate(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = (f >> 23) & 0xff;
  unsigned int frac = f & 0x7fffff;

  if (exp == 0xff && frac != 0) {
    // NaN
    return f;
  }

  return ((~sign) << 31) | (exp << 23) | frac;
}

// 2.93

/* compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = (f >> 23) & 0xff;
  unsigned int frac = f & 0x7fffff;


  if (exp == 0xff && frac != 0) {
    // NaN
    return f;
  }

  return (0 << 31) | (exp << 23) | frac;

}

// 2.94 
/* compute 2*f. If f is NaN, then return f. */
float_bits float_twice(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = (f >> 23) & 0xff;
  unsigned int frac = f & 0x7fffff;


  if (exp == 0xff) {
    // infinity or NaN
    return f;
  }

  if (exp == 0) {
    /* denormalized */
    frac <<= 1;
  } else if (exp == 0xFE) {
    // infinity
    exp = 0xFF;
    frac = 0;
  } else {
    /* normalized */
    exp += 1;
  }

  return sign << 31 | exp << 23 | frac;
}

// 2.95
/* compute 0.5*f. If f is NaN, then return f. */
float_bits float_half(float_bits f) {
  unsigned int sign = f >> 31;
  unsigned int exp = (f >> 23) & 0xff;
  unsigned int frac = f & 0x7fffff;

  if (exp == 0xff) {
    // infinity or NaN
    return f;
  }

  
}

int main() {
  // 2.57
  test_show_bytes(3);

  // 2.58
  printf("is_little_endian: %d\n", is_little_endian());
  
  // 2.59
  printf("0x%x\n", gen_word(0x89ABCDEF, 0x76543210));
  
  // 2.60
  assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
  assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);

  // 2.61

  int all_bit_one = ~0;
  int all_bit_zero = 0;

  assert(A(all_bit_one));
  assert(!B(all_bit_one));
  assert(C(all_bit_one));
  assert(!D(all_bit_one));

  assert(!A(all_bit_zero));
  assert(B(all_bit_zero));
  assert(!C(all_bit_zero));
  assert(D(all_bit_zero));

  assert(!A(0x1234ff));
  assert(!B(0x1234ff));
  assert(C(0x1234ff));
  assert(D(0x1234ff));

  // 2.62
  printf("int_shifts_are_arithmetic: %d\n", int_shifts_are_arithmetic());

  // 2.63
  unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;
  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);

  // 2.64
  assert(any_odd_one(0x2) == 1);
  assert(any_odd_one(0x4) == 0);

  // 2.65
  assert(odd_ones(0x2) == 1);
  assert(odd_ones(0x6) == 0);

  // 2.66

  assert(leftmost_one(0xFF00) == 0x8000);
  assert(leftmost_one(0x6000) == 0x4000);
  assert(leftmost_one(0x0) == 0x0);

  // 2.67
  assert(int_size_is_32());
  assert(int_size_is_32_for_16bit());

  // 2.68
  assert(lower_one_mask(6) == 0x3f);
  assert(lower_one_mask(17) == 0x1FFFF);

  // 2.69
  assert(rotate_left(0x12345678, 4) == 0x23456781);
  assert(rotate_left(0x12345678, 20) == 0x67812345);
  assert(rotate_left(0x12345678, 0) == 0x12345678);
  
  // 2.70
  assert(fits_bits(0xff, 8) == 0);
  assert(fits_bits(~0xff, 8) == 0);

  // 2.71
  assert(xbyte(0x00112233, 0) == 0x33);
  assert(xbyte(0x00112233, 1) == 0x22);
  assert(xbyte(0x00112233, 2) == 0x11);
  assert(xbyte(0x00112233, 3) == 0x00);

  assert(xbyte(0xAABBCCDD, 0) == 0xFFFFFFDD);
  assert(xbyte(0xAABBCCDD, 1) == 0xFFFFFFCC);
  assert(xbyte(0xAABBCCDD, 2) == 0xFFFFFFBB);
  assert(xbyte(0xAABBCCDD, 3) == 0xFFFFFFAA);

  // 2.72
  int maxbytes = sizeof(int) * 10;
  void* buf = malloc(maxbytes);
  int val;

  val = 0x12345678;
  copy_int(val, buf, maxbytes);
  assert(*(int*)buf == val);

  val = 0xAABBCCDD;
  copy_int(val, buf, 0);
  assert(*(int*)buf != val);

  free(buf);

  // 2.73

  assert(INT_MAX == saturating_add(INT_MAX, 0x1234));
  assert(INT_MIN == saturating_add(INT_MIN, -0x1234));
  assert(0x33 == saturating_add(0x11, 0x22));

  // 2.74
  assert(tsub_ok(-1, INT_MIN) == 1);
  assert(tsub_ok(1, INT_MIN) == 0);
  assert(tsub_ok(0, INT_MIN) == 0);
  assert(tsub_ok(INT_MIN, INT_MIN) == 1);
  assert(tsub_ok(0, 0) == 1);

  // 2.75

  unsigned x = 0x12345678;
  unsigned y = 0xFFFFFFFF;
  assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));

  // 2.76

  void* p;
  p = another_calloc(0x1234, 1);
  assert(p != NULL);
  free(p);

  p = another_calloc(SIZE_MAX, 4096);
  assert(p == NULL);
  free(p);

  // 2.77

  x = 0x87654321;
  assert(Amul(x) == 17 * x);
  assert(Bmul(x) == -7 * x);
  assert(Cmul(x) == 60 * x);
  assert(Dmul(x) == -112 * x);

  // 2.78
  int m = 0xFFFFFFFF;
  int n = 7;
  assert(divide_power2(m, 1) == m / 2);
  assert(divide_power2(n, 2) == n / 4);

  // 2.79
  
  m = INT_MAX;
  n = INT_MIN;
  assert(mul3div4(m) == m * 3 / 4);
  assert(mul3div4(n) == n * 3 / 4);
  assert(mul3div4(-1) == -1 * 3 / 4);
  assert(mul3div4(1) == 1 * 3 / 4);

  // 2.80
  assert(threefourths(8) == 6);   // 0x1000
  assert(threefourths(9) == 6);   // 0x1001
  assert(threefourths(10) == 7);  // 0x1010 
  assert(threefourths(11) == 8);  // 0x1011


  assert(threefourths(-8) == -6);
  assert(threefourths(-9) == -6);
  assert(threefourths(-10) == -7);
  assert(threefourths(-11) == -8);  

  // 2.81
  assert(genA(8) == 0xFFFFFF00);
  assert(genB(16, 8) == 0x00FFFF00);

  // 2.84
  assert(float_le(-0, +0));
  assert(float_le(+0, -0));
  assert(float_le(0, 3));
  assert(float_le(-4, -0));
  assert(float_le(-4, 4));
  assert(float_le(4, -4) == 0);

  // 2.89
  
  int ix = INT_MAX;
  double dx = (double) ix;
  assert(fA(ix, dx));

  ix = 0;
  dx = (double) ix;
  int iy = INT_MIN;
  double dy = (double) iy;
  assert(fB(ix, dx, iy, dy) == 0);


  ix = 3;
  iy = 1e9;
  int iz = 1e9;

  dx = (double) ix;
  dy = (double) iy;
  double dz = (double) iz;
  
  assert(fC(dx, dy, dz));
  assert(fD(dx, dy, dz));
  assert(fE(dx, dz));

  // 2.90

  assert(fpwr2(-10000) == powf(2,-10000));
  assert(fpwr2(-149) == powf(2,-149));
  assert(fpwr2(-130) == powf(2,-130));
  assert(fpwr2(-126) == powf(2,-126));
  assert(fpwr2(0) == powf(2,0));
  assert(fpwr2(128) == powf(2,128));
  assert(fpwr2(10000) == powf(2,10000));

  //2.92
 
  assert(u2f(float_negate(f2u(-1.0))) == 1.0);
  assert(float_negate(0x89999999)==0x09999999);
  assert(float_negate(0x7F900000)==0x7F900000);

  // 2.93
  assert(u2f(float_absval(f2u(-1.5))) == 1.5);
  assert(float_absval(0x89)==0x89);
  assert(float_absval(0x89999999)==0x09999999);
  assert(float_absval(0x7F900000)==0x7F900000);

  // 2.94
  printf("%f\n", u2f(float_twice(f2u(0.013672))));
  assert(u2f(float_twice(f2u(1.0))) == 2.0);
  
  // 2,95
  
}