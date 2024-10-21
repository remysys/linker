#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

sigjmp_buf buf;

void handler(int sig) {
  char c;
  signal(sig, SIG_IGN);
  printf("\nAh, Ctrl-C?\n");
  printf("Want to quit?");
  c = getchar();
  if (c == 'y' || c == 'Y') {
    exit(0);
  } else {
    signal(SIGINT, handler);
    siglongjmp(buf, 1);
  }
}


int main(void) {
  signal(SIGINT, handler);
  while (1) {
    if (sigsetjmp(buf, 1)==0) {
      printf("Hit Ctrl-C …\n");
      pause();
    }
  }

  return 0;
}