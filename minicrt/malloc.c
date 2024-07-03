/* 
 * https://www.pengrl.com/p/20032/ 
 * https://fossd.anu.edu.au/linux/v2.6.25/source/mm/mmap.c#L240 
 */

#include "minicrt.h"

typedef struct _heap_header {
  enum{
    HEAP_BLOCK_FREE  = 0XABABABAB,
    HEAP_BLOCK_USED  = 0XCDCDCDCD
  } type;

  unsigned int size;
  struct  _heap_header* next;
  struct  _heap_header* prev; 
} heap_header;

#define ADDR_ADD(a,o) (((char*)(a)) + o)
#define HEADER_SIZE  (sizeof(heap_header))

static heap_header* list_head  = NULL;

void free(void* ptr) {
  heap_header* header  = (heap_header*)ADDR_ADD(ptr, -HEADER_SIZE);
  if (header->type != HEAP_BLOCK_USED) {
    return ;
  }

  header->type  = HEAP_BLOCK_FREE;
  if (header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE) {
    // merge 
    header->prev->next = header->next;
    if(header->next != NULL)
      header->next->prev = header->prev;
    
    header->prev->size += header->size;
    header  = header->prev;
  }

  if (header->next != NULL && header->next->type == HEAP_BLOCK_FREE) {
    // merge
    header->size += header->next->size;
    header->next = header->next->next;
  }
}

void* malloc(unsigned int size) {
  heap_header *header;
  if (size == 0) {
    return NULL;
  }

  header  = list_head;
  while(header != 0) {
    if (header->type == HEAP_BLOCK_USED) {
      header = header->next;
      continue;
    }

    if ((header->size > size + HEADER_SIZE) && (header->size <= size + HEADER_SIZE*2)) {
      header->type = HEAP_BLOCK_USED;
      return ADDR_ADD(header, HEADER_SIZE);
    }

    if (header->size > size + HEADER_SIZE*2) {
      // split
      heap_header* next = (heap_header*)ADDR_ADD(header, size + HEADER_SIZE);
      next->prev  = header;
      next->next  = header->next;
      next->type  = HEAP_BLOCK_FREE;
      next->size  = header->size - (size - HEADER_SIZE);
      header->next  = next;
      header->size  = size + HEADER_SIZE;
      header->type  = HEAP_BLOCK_USED;
      return ADDR_ADD(header, HEADER_SIZE);
    }

    header = header->next;
  }

  return NULL;
}


// linux brk system call
// https://fossd.anu.edu.au/linux/v2.6.25/source/mm/mmap.c#L240

static void *brk(void *addr) {
  unsigned int ret  = 0;

  //#define __NR_brk 45
  asm("movl $45, %%eax    \n\t"
      "movl %1, %%ebx     \n\t"
      "int $0x80          \n\t"
      "movl %%eax, %0     \n\t"
      :"=r"(ret):"m"(addr));

  // no need for explicit return as the return value is already in eax
  // return ret;
}

int mini_crt_init_heap() {
  void *base  = NULL;
  heap_header *header  = NULL;

  int ret = 0;

  //32MB heap size
  unsigned heap_size  = 1024*1024*32;

  base = (void *)brk(0);
  void *new_brk = ADDR_ADD(base, heap_size);
  new_brk = (void *)brk(new_brk);

  if (new_brk == base) {
    return -1;
  }

  header = (heap_header*)base;

  header->size = heap_size;
  header->type = HEAP_BLOCK_FREE;
  header->next = NULL;
  header->prev = NULL;

  list_head = header;
  return 0;
}