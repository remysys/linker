typedef void (*ctor_func)(void);
// replace .ctors/.dtors with .init_array/.fini_array
ctor_func crt_end[1] __attribute__ ((section(".init_array"))) =  {
  (ctor_func) -1
};