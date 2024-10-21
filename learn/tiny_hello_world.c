/*
 * tiny hello world.
 * gcc -c -fno-builtin tiny_hello_world.c
 * ld -static -e nomain -o tiny_hello_world tiny_hello_world.o
 * ld -static -T tiny_hello_world.lds -o tiny_hello_world tiny_hello_world.o
 */

char* str = "Hello world!\n";

void print() {
  asm("movl $13, %%edx\n\t"
      "movq %0, %%rcx\n\t"
      "movl $0, %%ebx\n\t"
      "movl $4, %%eax\n\t"
      "int $0x80 \n\t"
      ::"r"(str):"edx","ecx","ebx");
}

void exit() {
  asm("movl $42,%ebx\n\t"
      "movl $1, %eax\n\t"
      "int $0x80 \n\t");
}

void nomain() {
  print();
  exit();
}