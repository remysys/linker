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
  return !(x ^ ~0);
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
  return 0;

  // 2.63
  unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;
  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);

}