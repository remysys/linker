def rotate_letter(letter, n):
  if letter.isupper():
    start = ord('A')
  elif letter.islower():
    start = ord('a')
  else:
    return letter
  
  c = ord(letter) - start
  i = (c + n) % 26 + start
  return chr(i)

def rotate_word(word, n):
  res = ''
  for letter in word:
      res += rotate_letter(letter, n)
  return res

def make_word_dict():
  d = dict()
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    d[word] = None
  
  return d

def rotate_pairs(word_dict, word):
  for i in range(1, 26):
    rotated = rotate_word(word, i)
    if rotated in word_dict:
      print(word, i, rotated)


if __name__ == '__main__':
  word_dict = make_word_dict()

  for word in word_dict:
    rotate_pairs(word_dict, word)
  