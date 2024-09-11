
import math

def mysqrt(a):
  x = a / 2;
  epsilon = 0.0000001
    
  while True:
    y = (x + a/x) / 2;
    if abs(y - x) < epsilon:
      break;
    x = y;
  
  return x;

def test_square_root():
  print("a\tmysqrt(a)\tmath.sqrt(a)\tdiff")
  print("-\t---------\t------------\t----")

  a = 1.0
  while a < 10:
    mys = mysqrt(a)
    mths = math.sqrt(a)
    diff = abs(mys - mths)
    print("{0:.1f}\t{1:.7f}\t{2:.10f}\t {3:.2f}".format(a, mys, mths, diff))
    a += 1

test_square_root()