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

  return count, d

if __name__ == '__main__':
  count, d = process_file('emma.txt')
  print(count)
  print(d)