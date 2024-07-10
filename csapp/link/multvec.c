// gcc -c addvec.c multvec.c
// ar rcs libvector.a addvec.o multvec.o 
// gcc -shared -fpic -o libvector.so addvec.c multvec.c

int multcnt = 0;

void multvec(int *x, int *y, int *z, int n) {
  int i;
  multcnt++;

  for (i = 0; i < n; i++) {
    z[i] = x[i] * y[i];
  }
}