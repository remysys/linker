typedef void (*ctor_func)(void);
// replace .ctors/.dtors with .init_array/.fini_array

ctor_func ctors_begin[1] __attribute__ ((section(".init_array"))) = {
    (ctor_func) -1
};

void run_hooks() {
  const ctor_func *list = ctors_begin;
  while ((int)*++list != -1) {
    (**list)();
  }
}