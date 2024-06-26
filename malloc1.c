#include <stdio.h>
#include <malloc.h>

int main() { 
  // allocate 1 byte
  void *addr = malloc(1); 
  printf("start address: %x\n", addr); 
  printf("cat /proc/%d/maps\n",getpid()); 

  getchar();
   
  // free mem
  free(addr); 
  printf("1 byte of memory is released but the heap is not deallocated\n"); 
  getchar(); 
  return 0; 
}