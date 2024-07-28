
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void test_show_bytes(int val) {
  int ival = val;
  float fval = (float) ival;
  int *pval = &ival;
  show_int(ival);
  show_float(fval);
  show_pointer(pval);
}

void simple_show_a() {
  int val = 0x87654321;
  byte_pointer valp = (byte_pointer) &val;
  show_bytes(valp, 1); /* A. */
  show_bytes(valp, 2); /* B. */
  show_bytes(valp, 3); /* C. */
}

void simple_show_b() {
  int val = 0x12345678;
  byte_pointer valp = (byte_pointer) &val;
  show_bytes(valp, 1); /* A. */
  show_bytes(valp, 2); /* B. */
  show_bytes(valp, 3); /* C. */
}


void string_ueg() {
  const char *s = "ABCDEF";
  show_bytes((byte_pointer) s, strlen(s)); 
}

void string_leg() {
  const char *s = "abcdef";
  show_bytes((byte_pointer) s, strlen(s)); 
}

void inplace_swap(int *x, int *y) {
  printf("x = %d y = %d\n", *x, *y);
  *y = *x ^ *y; 
  *x = *x ^ *y; 
  *y = *x ^ *y;
  printf("x = %d y = %d\n", *x, *y);
}

void show_shift() {
  int lval = 0xFEDCBA98 << 32;
  int aval = 0xFEDCBA98 >> 36;
  unsigned uval = 0xFEDCBA98u >> 40;

  printf("lval: 0x%x aval: 0x%x uval: 0x%x\n", lval, aval, uval);
}

void show_twocomp() {
  short x = 12345; 
  short mx = -x; 
  
  show_bytes((byte_pointer) &x, sizeof(short)); 
  show_bytes((byte_pointer) &mx, sizeof(short)); 
}


void show_example() {
  short sx = -12345;  /* -12345 */
  unsigned uy = sx;   /* mystery! */

  printf("uy = %u:\t", uy);
  show_bytes((byte_pointer) &uy, sizeof(unsigned));

  int z = 53191;
  short sz = (short) z; /* -12345 */
  int y = sz; /* -12345 */

  printf("sz = %d y = %d\n", sz, y);
  show_bytes((byte_pointer) &z, sizeof(int));
  show_bytes((byte_pointer) &sz, sizeof(short));
  show_bytes((byte_pointer) &y, sizeof(int));
}

int main(int argc, char *argv[]) {
  int val = 12345;

  if (argc > 1) {
    val = strtol(argv[1], NULL, 0);
    printf("calling test_show_bytes\n");
    test_show_bytes(val);
  } else {
    printf("Calling simple_show_a\n");
    simple_show_a();
    printf("Calling simple_show_b\n");
    simple_show_b();
    printf("Calling string_ueg\n");
    string_ueg();
    printf("Calling string_leg\n");
    string_leg();
    int a = 10;
    int b = 20;
    inplace_swap(&a, &b);
    inplace_swap(&a, &a);
    show_shift();
    printf("calling show_twocomp\n");
    show_twocomp();
    show_example();
  }
  return 0;
}