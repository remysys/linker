def make_word_list():
  t = []
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    t.append(word)
  
  return t

def in_bisect(word_list, word):
  if len(word_list) == 0:
    return False
  
  i = len(word_list) // 2
  
  if word == word_list[i]:
    return True

  if word < word_list[i]:
    return in_bisect(word_list[:i], word)
  else:
    return in_bisect(word_list[i + 1:], word)

def reverse_pair(word_list, word):
  reverse_word = word[::-1]
  return in_bisect(word_list, reverse_word)

def main():
  word_list = make_word_list()
  
  for word in word_list:
    if reverse_pair(word_list, word):
      print(word, word[::-1])

main()