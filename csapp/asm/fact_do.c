/* gcc -Og -S fact_do.c */
#include <stdio.h>

long fact_do(long n) {
  long result = 1;

  do {
    result *= n;
    n = n - 1;
  } while (n > 1);

  return result;
}

int fact_do_overflow(int n) {
  int result = 1;

  do {
    result *= n;
    n = n-1;
  } while (n > 1);

  return result;
}

int main() {
  printf("fact_do_overflow(14) = %d\n", fact_do_overflow(14));
  return 0;
}