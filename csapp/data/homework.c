#include <stdio.h>
#include <assert.h>

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

int main() {
  // 2.57
  test_show_bytes(12345);

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
  
}