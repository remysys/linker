#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int result;

void fact(int res, int count, int n) {
  if (count <= n) {
    fact(res * count, count + 1, n);
  } else {
    result = res;
    longjmp(buf, 1);
  }
}

void factorial(int n) {
  fact(1, 1, n);
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  if (setjmp(buf) == 0) {
    factorial(n);
  } else {
    printf("%d! = %d\n", n, result);
  }

  return 0;
}