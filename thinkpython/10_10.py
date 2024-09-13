import bisect

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

def in_bisect_cheat(word_list, word):
    i = bisect.bisect_left(word_list, word)
    if i == len(word_list):
        return False

    return word_list[i] == word

def main():
  word_list = make_word_list()

  for word in ['aa', 'alien', 'allen', 'zymurgy']:
    print(word, 'in list', in_bisect(word_list, word))

  for word in ['aa', 'alien', 'allen', 'zymurgy']:
    print(word, 'in list', in_bisect_cheat(word_list, word))

main()