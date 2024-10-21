#include<stdio.h>

#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)
#define DEBUG(...) printf(__VA_ARGS__)

int main(void) {
  LOG("Hello %s\n", "World");
  DEBUG("Hello %s\n", "World");

  DEBUG("Hello World\n");
  return 0;
}