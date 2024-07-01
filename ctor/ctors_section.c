/*
 * gcc version < 4.7  => .ctors
 * gcc version >= 4.7 => .init_array
 * objdump -s -j .init_array a.out
 */
#include <stdio.h>

void my_init(void) {
  printf("Hello ");
}

typedef void (*ctor_func)(void);
ctor_func __attribute__((section (".ctors"))) my_init_p = &my_init;

int main() {
  printf("World\n");
  printf("%p\n", &my_init_p);
  printf("%p\n", my_init);
  return 0;
}