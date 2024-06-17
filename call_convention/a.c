
/*
 * gcc -m32 a.c ./b.so
 * https://gcc.gnu.org/onlinedocs/gcc/x86-Function-Attributes.html
 */
void __attribute__((fastcall)) foo(int, int);

int main() {
  foo(1, 3);
  return 0;
}