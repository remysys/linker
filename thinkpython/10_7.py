def has_duplicates(s):
  # make a copy of t to avoid modifying the parameter
  t = list(s)
  t.sort()

  # check for adjacent elements that are equal
  for i in range(len(t) - 1):
    if t[i] == t[i + 1]:
      return True
  
  return False

print(has_duplicates([1, 2, 2]))
print(has_duplicates("remyy"))
print(has_duplicates("remy"))