// gcc atexit.c
#include <stdio.h>
#include <stdlib.h>

void foo1() {
  printf("foo1 called\n");
}

void foo2() {
  printf("foo2 called\n");
}

int main() {
  atexit(foo1);
  atexit(foo2);

  printf("main func called\n");

  return 0;
}