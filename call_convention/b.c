/*
 * gcc -m32 -shared -fPIC b.c -o b.so
 * https://gcc.gnu.org/onlinedocs/gcc/x86-Function-Attributes.html
 */

#include<stdio.h>

void __attribute__((cdecl)) foo(int a, int b) {
  printf("a=%d, b=%d\n", a, b);
}