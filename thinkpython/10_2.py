def cumsum(t):
  total = 0;
  res = []
  for x in t:
    total += x
    res.append(total)
  
  return res

print(cumsum([1, 2, 3]))

