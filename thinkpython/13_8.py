import string
import random

suffix_map = {}
prefix = ()

def shift(prefix, word):
  return prefix[1:] + (word, )

def process_line(line, order = 2):
  global prefix
  line = line.replace('-', ' ')
  strippables = string.punctuation + string.whitespace
  for word in line.split():
    word = word.strip(strippables).lower()
    if len(prefix) < order:
      prefix += (word,)
      continue
    
    if prefix in suffix_map:
      suffix_map[prefix].append(word)
    else:
      suffix_map[prefix] = [word]

    prefix = shift(prefix, word)

def skip_header(fp):
  for line in fp:
    if line.startswith('*** START OF THIS'):
      break

def process_file(filename, order = 2):
  fp = open(filename)

  skip_header(fp)

  for line in fp:
    if line.startswith('*** END OF THIS'):
      break
    process_line(line, order)

def random_text(n = 100):
  
  # choose a random prefix (not weight by frequency)
  start = random.choice(list(suffix_map.keys()))

  for i in range(n):
    suffixes = suffix_map.get(start, None)
    if suffixes == None:
      random_text(n - i)
      return 
    word = random.choice(suffixes)
    print(word, end = ' ')
    start = shift(start, word)

if __name__ == '__main__':
  process_file('emma.txt', 2)
  random_text(10)
  print()