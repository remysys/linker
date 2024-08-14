#include <stdio.h>
#include <stddef.h>

struct P1 { short i; int c; int *j; short *d; };
struct P2 { int i[2]; char c[8]; short s[4]; long *j; };
struct P3 { long w[2]; int *c[2]; };
struct P4 { char w[16]; char *c[2]; };
struct P5 { struct P4 a[2]; struct P1 t; };

struct P6 {
  int *a;  
  float b; 
  char c;  
  short d; 
  long e;  
  double f;
  int g;   
  char *h; 
};

/* 
 * rearrange the fields of the structure P6
 * order the structure elements in descending order of size
 */

struct P7 {
  int *a;
  long e;  
  double f;
  char *h;
  int g;
  float b; 
  short d; 
  char c;    
};

// #define offsetof(s, m) (size_t)((char*)(&((s*)0)->m)) 

int main() {
  printf("sizeof(P1) = %u\n", sizeof(struct P1));
  printf("sizeof(P2) = %u\n", sizeof(struct P2));
  printf("sizeof(P3) = %u\n", sizeof(struct P3));
  printf("sizeof(P4) = %u\n", sizeof(struct P4));
  printf("sizeof(P5) = %u\n", sizeof(struct P5));
  printf("sizeof(P6) = %u\n", sizeof(struct P6));
  printf("sizeof(P7) = %u\n", sizeof(struct P7));

  printf("offsets of fields in struct P6:\n");
  printf("a: %zu\n", offsetof(struct P6, a));
  printf("b: %zu\n", offsetof(struct P6, b));
  printf("c: %zu\n", offsetof(struct P6, c));
  printf("d: %zu\n", offsetof(struct P6, d));
  printf("e: %zu\n", offsetof(struct P6, e));
  printf("f: %zu\n", offsetof(struct P6, f));
  printf("g: %zu\n", offsetof(struct P6, g));
  printf("h: %zu\n", offsetof(struct P6, h));

  printf("offsets of fields in struct P7:\n");
  printf("a: %zu\n", offsetof(struct P7, a));
  printf("e: %zu\n", offsetof(struct P7, e));
  printf("f: %zu\n", offsetof(struct P7, f));
  printf("h: %zu\n", offsetof(struct P7, h));
  printf("g: %zu\n", offsetof(struct P7, g));
  printf("b: %zu\n", offsetof(struct P7, b));
  printf("d: %zu\n", offsetof(struct P7, d));
  printf("c: %zu\n", offsetof(struct P7, c));

  return 0;
}

