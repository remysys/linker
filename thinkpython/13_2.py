import string

def process_line(line, hist):
  line = line.replace('-', ' ')
  strippables = string.punctuation + string.whitespace
  for word in line.split():
    word = word.strip(strippables).lower()
    hist[word] = hist.get(word, 0) + 1

def skip_header(fp):
  for line in fp:
    if line.startswith('*** START OF THIS'):
      break

def process_file(filename):
  hist = dict()
  fp = open(filename)

  skip_header(fp)

  for line in fp:
    if line.startswith('*** END OF THIS'):
      break
    
    process_line(line, hist)
  
  return hist 

def total_words(hist):
  return sum(hist.values())

def different_words(hist):
  return len(hist)


if __name__ == '__main__':
  hist = process_file('emma.txt')
  print ('total number of words:', total_words(hist))
  print ('number of different words:', different_words(hist))

