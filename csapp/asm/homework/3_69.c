#include <stdio.h>
#include <stddef.h>

typedef struct {
  long idx;
  long x[4];
} a_struct;

typedef struct {
  int first;
  a_struct a[7];
  int last;
} b_struct;

void test(long i, b_struct *bp) {
  int n = bp->first + bp->last;
  a_struct *ap = &bp->a[i];
  ap->x[ap->idx] = n;
}

int main() {
  printf("Size of a_struct: %zu bytes\n", sizeof(a_struct));

  printf("Offset of idx: %zu bytes\n", offsetof(a_struct, idx));
  printf("Offset of x[0]: %zu bytes\n", offsetof(a_struct, x[0]));
  printf("Offset of x[1]: %zu bytes\n", offsetof(a_struct, x[1]));
  printf("Offset of x[2]: %zu bytes\n", offsetof(a_struct, x[2]));
  printf("Offset of x[3]: %zu bytes\n", offsetof(a_struct, x[3]));
}