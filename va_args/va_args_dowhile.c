#include<stdio.h>

/*
#define DEBUG() \
  printf("hello "); printf("else\n")
*/


#define DEBUG() \
do { \
  printf("hello "); printf("else\n"); \
} while(0)

int main(void) {
  if(1)
    printf("hello if\n");
  else
  DEBUG();

  return 0;
}