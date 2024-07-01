#include <stdio.h>
/*
 * gcc version < 4.7  => .ctors
 * gcc version >= 4.7 => .init_array
 * objdump -s -j .init_array a.out
 */

void my_init(void) __attribute__ ((constructor));
void my_init(void) {
  printf("Hello ");
}

int main() {
  printf("World\n");
  printf("%p\n", my_init);
  return 0;
}