/*
 * gcc -m32 -g return_big_thing.c 
 * objdump -d a.out
 */
typedef struct big_thing {
  char buf[128];
} big_thing;

big_thing return_test() {
  big_thing b;
  b.buf[0] = 0;
  return b;
}

int main() {
  big_thing n = return_test();
}