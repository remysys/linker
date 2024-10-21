
#include <stdio.h>

int add(int a, int b) {
  return a + b;
}

int main()
{
  int a = 1;
  int b = 8;

  int res = add(a, b);
  printf("%d", res);
  return res;
}