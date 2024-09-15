import random

def histogram(s):
  d = dict()
  for c in s:
    d[c] = d.get(c, 0) + 1
  
  return d

def choose_from_hist(h):
  t = []
  for c, cnt in h.items():
    for i in range(cnt):
      t.append(c)
  
  return random.choice(t)

if __name__ == '__main__':
  h = histogram(['a', 'a', 'b'])
  for i in range(9):
    print(choose_from_hist(h))