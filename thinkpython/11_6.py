from pronounce import read_dictionary

def make_word_dict():
  d = dict()
  fin = open('words.txt')
  for line in fin:
    word = line.strip().lower()
    d[word] = word

  return d

def homophones(a, b, phonetic):
  if a not in phonetic or b not in phonetic:
    return False

  return phonetic[a] == phonetic[b]


def check_word(word, word_dict, phonetic):
  word1 = word[1:] 
  if word1 not in word_dict:
    return False
  if not homophones(word, word1, phonetic):
    return False

  word2 = word[0] + word[2:]
  if word2 not in word_dict:
    return False
  if not homophones(word, word2, phonetic):
    return False

  return True

if __name__ == '__main__':
  phonetic = read_dictionary()
  word_dict = make_word_dict()

  for word in word_dict:
    if check_word(word, word_dict, phonetic):
      print(word, word[1:], word[0] + word[2:])