// gcc -g -c main.c
// gcc -Og -static -o prog2c main.o ./libvector.a
// gcc -Og -static -o prog2c main.o -L. -lvector

// gcc -g -static -o prog main.c ./libvector.a
// gcc -g -o prog main.c ./libvector.so

#include <stdio.h>

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

extern int addcnt;
extern int multcnt;

void addvec(int *x, int *y, int *z, int n);
void multvec(int *x, int *y, int *z, int n);

int main() {
  addvec(x, y, z, 2);
  printf("z = [%d %d]\n", z[0], z[1]);

  printf("addcnt = %d\n", addcnt);
  return 0;
}