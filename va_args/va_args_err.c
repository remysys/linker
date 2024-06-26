#include<stdio.h>

// error
// #define LOG(fmt, ...) printf(fmt, __VA_ARGS__)

// succ
#define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__)

int main(void) {
  LOG("Hello World\n");
  return 0;
}