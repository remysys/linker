import string

def process_file(filename):
  d = dict()
  count = 0
  fin = open(filename)
  for line in fin:
    line = line.replace('-', ' ')
    for word in line.split():
      word = word.strip(string.punctuation + string.whitespace + string.digits + '”' + '“').lower()
      d[word] = d.get(word, 0) + 1
      count += 1
  
  t = []
  for word, cnt in d.items():
    t.append((cnt, word))
  t.sort(reverse = True)

  return count, t

if __name__ == '__main__':
  count, t = process_file('emma.txt')
  print(count)
  for i in range(20):
    print(t[i])

  
  