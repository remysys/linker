import math

def factorial(n):
  if n == 0:
    return 1
  else:
    return n * factorial(n-1)

def estimate_pi():
  total = 0
  k = 0
  factor = 2 * math.sqrt(2) / 9801
  while True:
    num = factorial(4*k) * (1103 + 26390*k)
    den = factorial(k)**4 * 396**(4*k)
    
    total += num / den
    term = factor * num/den
    
    if abs(term) < 1e-15:
      break
    k += 1
  
  return 1 / (factor * total)

print(estimate_pi())