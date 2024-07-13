// gcc -c main2.c
// gcc -Og -static -o prog2c main2.o ./libvector.a
// gcc -Og -static -o prog2c main2.o -L. -lvector
// error: gcc -static ./libvector.a main2.c
// gcc -g -o prog main2.c ./libvector.so
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
  multvec(x, y ,z, 2);
  printf("z = [%d %d]\n", z[0], z[1]);
  printf("addcnt = %d multcnt = %d\n", addcnt, multcnt);
  return 0;
}