// g++ -c hello.c
// objdump -dr hello.o
// c++filt _Znwm
class C {
};

int main() {
  C *c = new C();
  return 0;
}