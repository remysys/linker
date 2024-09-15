import string
import random
import bisect

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

def most_common(hist):
  t = []
  for key, value in hist.items():
    t.append((value, key))
  
  t.sort(reverse = True)
  return t

def print_most_common(hist, num = 10):
  t = most_common(hist)
  print('the most common words are: ')
  for freq, word in t[:num]:
    print(word, freq, sep = '\t')

def substract(d1, d2):
  return set(d1) - set(d2)

def random_word(hist):
  words = []
  freqs = []
  total_freq = 0

  for word, freq in hist.items():
    total_freq += freq
    words.append(word)
    freqs.append(total_freq)
  
  x = random.randint(0, total_freq - 1)
  index = bisect.bisect(freqs, x)
  return words[index]

if __name__ == '__main__':
  hist = process_file('emma.txt') 
  print("here are some random words from the book:")
  for i in range(10):
    print(random_word(hist))