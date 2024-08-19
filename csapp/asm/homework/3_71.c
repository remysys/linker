#include <stdio.h>

#define BUF_SIZE 16

void good_echo() {
  char buf[BUF_SIZE];

  while (fgets(buf, BUF_SIZE, stdin)) {
    // printf("%s", buf);
    fputs(buf, stdout);
  }
  
  return;
}

int main() {
  good_echo();
  return 0;
}