/* 
 * gcc -Og -S float_mov.c 
 * gcc -Og -mavx2 -S float_mov.c  
 */
float float_mov(float v1, float *src, float *dst) {
  float v2 = *src;
  *dst = v1;
  return v2;
}

double fcvt(int i, float *fp, double *dp, long *lp) {
  float f = *fp; 
  double d = *dp; 
  long l = *lp;
  
  *lp = (long) d;
  *fp = (float) i;
  *dp = (double) l;
  
  return (double) f;
}

double funct(double a, float x, double b, int i) {
  return a*x - b/i;
}

double cel2fahr(double temp) {
  return 1.8 * temp + 32.0;
}

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range(float x) {
  int result;
  
  if (x < 0)
    result = NEG;
  else if (x == 0)
    result = ZERO;
  else if (x > 0)
    result = POS;
  else
    result = OTHER;
  
  return result;
}