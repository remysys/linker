def has_duplicates(t):
  d = dict()
  for x in t:
    if x in d:
      return True
    d[x] = True
  
  return False

print(has_duplicates([1, 2, 2]))
print(has_duplicates("remyy"))
print(has_duplicates("remy"))