
def signature(word):
  t = list(word)
  t.sort()
  return ''.join(t)

def all_anagrams(filename):
  d = {}
  fin = open(filename)
  for line in fin:
    word = line.strip().lower()
    t = signature(word)
    
    if t not in d:
      d[t] = [word]
    else:
      d[t].append(word)

  return d

def print_anagrams(d):
  for v in d.values():
    if len(v) > 1:
      print(len(v), v)

def print_anagrams_in_order(d):
  t = []
  for v in d.values():
    if len(v) > 1:
      t.append((len(v), v))
  
  t.sort(reverse = True)
  
  for l, v in t:
    print(l, v)

def print_anagrams_n(d, n):
  for v in d.values():
    if len(v) == n:
      print(len(v), v)

  
if __name__ == '__main__':
  d = all_anagrams('words.txt')
  print_anagrams(d)
  print_anagrams_in_order(d)
  print_anagrams_n(d, 8)






