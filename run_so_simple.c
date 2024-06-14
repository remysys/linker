#include <stdio.h>
#include <dlfcn.h>

// gcc -o run_so_simple run_so_simple.c -ldl
// ./run_so_simple /lib64/libm.so.6
int main(int argc, char **argv) {
  void *handle;
  double (*func)(double);
  char *error;

  if ((handle = dlopen(argv[1], RTLD_NOW)) == NULL) {
    printf("open library %s error: %s\n", argv[1], dlerror());
    return -1;
  }

  func = dlsym(handle, "sin");
  if ((error = dlerror()) != NULL) {
    printf("symbol sin not found: %s\n", error);
  } else {
    printf("%f\n", func(3.1415926 / 2));
  }
  
  dlclose(handle);

  return 0;
}