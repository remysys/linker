import string

def make_word_dict(filename):
  word_dict = {}
  fin = open(filename)
  for line in fin:
    word = line.strip().lower()
    word_dict[word] = None

  return word_dict

def print_words(filename, word_dict):
  hist = {}
  fin = open(filename)
  for line in fin:
    line = line.replace('-', ' ')
    for word in line.split():
      word = word.strip(string.punctuation + string.whitespace + string.digits + '”' + '“').lower()
      hist[word] = hist.get(word, 0) + 1

  t = list()
  for word in hist:
    if word not in word_dict:
      t.append((hist[word], word))
  
  t.sort()
  print(t)

if __name__ == '__main__':
  word_dict = make_word_dict('words.txt')
  print_words('emma.txt', word_dict)