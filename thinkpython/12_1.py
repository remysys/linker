def make_histogram(s):
  hist = {}
  for c in s:
    hist[c] = hist.get(c, 0) + 1

  return hist


def most_frequent(s):
  hist = make_histogram(s)

  t = list()
  for c, freq in hist.items():
    t.append((freq, c))
  
  t.sort(reverse = True)      # sort by freq

  for freq, c in t:
    print(c, freq)

if __name__ == '__main__':
  s = open('emma.txt').read()  # returns the contents of a file as a string
  most_frequent(s)



