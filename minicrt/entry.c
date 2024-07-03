#include "minicrt.h"

extern int main(int agrc,char *argv[]);
void exit(int);

static void crt_fatal_error(const char *msg) {
  printf("fatal error: %s\n", msg);
  exit(1);
}

void mini_crt_entry(void) {
  int ret;

  int argc;
  char** argv;
  char* ebp_reg  = 0;
  
  //ebp_reg = %ebp
  asm volatile ("movl %%ebp, %0\n":"=r"(ebp_reg));

  argc  = *(int*)(ebp_reg + 4);
  argv  = (char**)(ebp_reg + 8);


  if (mini_crt_init_heap()) {
    crt_fatal_error("heap initalize failed");
  }

  if (mini_crt_init_io()) {
    crt_fatal_error("io initalize failed");
  }

  ret  = main(argc, argv);
  exit(ret);
}

void exit(int code) {
  //mini_crt_call_exit_routine();

  asm("movl %0,%%ebx   \n\t" 
      "movl $1,%%eax   \n\t"
      "int $0x80       \n\t"
      "hlt             \n\t"::"m"(code));
}