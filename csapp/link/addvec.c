// gcc -c addvec.c multvec.c
// ar rcs libvector.a addvec.o multvec.o 
// gcc -g -shared -fpic -o libvector.so addvec.c multvec.c

int addcnt = 0;

void addvec(int *x, int *y, int *z, int n)  {
  int i;
  addcnt++;

  for (i = 0; i < n; i++) {
    z[i] = x[i] + y[i];
  }
}