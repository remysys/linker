def gcd(a, b):
  if b == 0:
    return a
  return gcd(b, a % b)

# example usage
print(gcd(48, 18))  # output: 6
print(gcd(56, 98))  # output: 14