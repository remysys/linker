/* 
 * gcc proc_stack.c -m32 -o proc_stack -g
 * gdb --args ./proc_stack 1 2 3 4
 */

#include <stdio.h>
#include <elf.h>

int main(int argc, char* argv[])
{
  int *p = (int *)argv;
  int i;
  Elf32_auxv_t* aux;

  printf("argument count: %d\n", *(p - 1));

  for(i = 0; i < *(p - 1); i++) {
    printf("argument %d : %s\n", i, *(p + i));
  }

  p += i;
  p++; //skip 0

  printf("environment:\n");
  while(*p) {
    printf("%s\n", *p);
    p++;
  }

  p++; //skip 0

  printf("auxiliary vectors:\n");
  aux = (Elf32_auxv_t *)p;
  while(aux->a_type != AT_NULL){
    printf("Type: %02d Value: %x\n", aux->a_type, aux->a_un.a_val);
    aux++;
  }
    
  return 0;
}