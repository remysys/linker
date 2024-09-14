import string

def process_file(filename):
  t = list()
  fin = open(filename)
  for line in fin:
    line = line.replace('-', ' ')
    for word in line.split():
      word = word.strip(string.punctuation + string.whitespace + string.digits + '”' + '“').lower()
      t.append(word)

  return t

if __name__ == '__main__':
  print(process_file('emma.txt'))

