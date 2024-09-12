
def is_palindrome(i, j):
  return str(i).zfill(2) == str(j).zfill(2)[::-1]


def num_instances(diff, show):
  daughter = 0
  count = 0

  while True:
    mother = daughter + diff
    if is_palindrome(daughter, mother):
      count = count + 1
      if show:
        print(daughter, mother)
    
    if mother > 120:
      break
    
    daughter = daughter + 1
  
  return count
    

def check_diffs():
  diff = 10
  while diff < 70:
    n = num_instances(diff, False)
    if (n == 8):
      print('daughter  mother')
      num_instances(diff, True)
    
    diff = diff + 1


check_diffs()