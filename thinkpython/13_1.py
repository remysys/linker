import string

def process_line(line, hist):
  line = line.replace('-', ' ')
  strippables = string.punctuation + string.whitespace
  for word in line.split():
    word = word.strip(strippables).lower()
    hist[word] = hist.get(word, 0) + 1

def process_file(filename):
  hist = dict()
  fp = open(filename)
  for line in fp:
    process_line(line, hist)
  
  return hist 

if __name__ == '__main__':
  hist = process_file('emma.txt')
  print(hist)

