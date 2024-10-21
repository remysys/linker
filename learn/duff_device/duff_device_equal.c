// gcc duff_device.c
#include <stdio.h>

int main() {
  int count = 100;
  int sum = 0;
  int n = (count + 7) / 8;

  // The number of iterations may not be divisible by the unrolling factor,
  // so additional handling is needed for the remainder of the division;
  // In this switch statement, there is no break statement,
  // which means it will automatically continue executing the case 
  // matching the remainder and proceed to the next case."
  
  switch (count % 8) {
    case 0: sum++;
    case 7: sum++;
    case 6: sum++;
    case 5: sum++;
    case 4: sum++;
    case 3: sum++;
    case 2: sum++;
    case 1: sum++;
  }

  // unroll the loop 8 times
  while (--n > 0) {
    sum++;
    sum++;
    sum++;
    sum++;
    sum++;
    sum++;
    sum++;
    sum++;
  }

  printf("sum: %d\n", sum);
  return 0;
}