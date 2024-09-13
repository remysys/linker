def nested_sum(t):

  total = 0
  for nested in t:
    total += sum(nested)
  
  return total

t = [[1 , 2] , [3] , [4 , 5 , 6]]
print(nested_sum(t))