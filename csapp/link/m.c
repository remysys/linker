/* 
 * gcc -Og -c m.c
 * readelf -s m.o
 */
 
void swap();

int buf[2] = {1, 2};

int main() {
  swap();
  return 0;
}