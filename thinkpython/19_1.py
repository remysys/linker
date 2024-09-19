import time

def binomial_coeff(n, k):
  return 1 if k == 0 else (0 if n == 0 else binomial_coeff(n - 1, k) + binomial_coeff(n - 1, k - 1))

memo = {}
def binomial_coeff_memo(n, k):
  if (n, k) in memo:
    return memo[(n, k)]

  result = 1 if k == 0 else (0 if n == 0 else binomial_coeff_memo(n - 1, k) + binomial_coeff_memo(n - 1, k - 1))
  memo[(n, k)] = result
  return result


if __name__ == '__main__':

  start = time.time()
  r = binomial_coeff(50, 5)
  end = time.time()
  print("the answer is: %d" % r)
  print("the time for the non-memoized version is: %.4f"% (end - start))

  start = time.time()
  r = binomial_coeff_memo(50, 5)
  end = time.time()
  print("the answer is: %d" % r)
  print("the time for the memoized version is: %.4f"% (end - start))

