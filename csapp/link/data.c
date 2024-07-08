// gcc -Og -c data.c
// gcc -Og -o prog data.c
// objdump -t data.o
// readelf -s data.o
// objdump -x prog to check all variable in which section 
#include <stdio.h>

int var1;               // COMMON(in data.o) .bss(in prog)  in .symtab
int var2 = 0;           // .bss  in .symtab
int var3 = 1;           // .data in .symtab

static int s_var1;      // .bss   not in .symtab
static int s_var2 = 0;  // .bss   not in .symtab
static int s_var3 = 1;  // .data  not in .symbab

int main() {
  static int ls_var1;     // .bss  not in .symtab
  static int ls_var2 = 0; // .bss  not in .symtab
  static int ls_var3 = 1; // .data not in .symtab

  printf("&s_var1: 0x%x &s_var2: 0x%x &s_var3: 0x%x\n&ls_var1: 0x%x &ls_var2: 0x%x &ls_var3: 0x%x\n", 
          &s_var1, &s_var2, &s_var3, &ls_var1, &ls_var2, &ls_var3);
  return 0;
}