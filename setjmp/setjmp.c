// gcc setjmp.c

#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void f() {
  longjmp(env, 0);
}

int main() {
  int ret = setjmp(env);
  printf("ret: %d\n");
  if (ret) {
    printf("World\n");
  } else {
    printf("Hello ");
    f();
  }

  return 0;
}