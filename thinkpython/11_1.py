import time
def make_word_list():
  t = []
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    t.append(word)
  return t

def histogram(word_list):
  d = dict()
  for word in word_list:
    d[word] = d.get(word, 0)
  return d

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

def main():
  word_list = make_word_list()
  h = histogram(word_list)

  key = "remy"

  start_time = time.time()

  if key in h:
    print(key, h[key])

  elapsed_time = time.time() - start_time
  print(f"{elapsed_time:.6f} seconds")

  start_time = time.time()
  if in_bisect(word_list, key):
    print(key, h[key])
  elapsed_time = time.time() - start_time
  print(f"{elapsed_time:.6f} seconds")

main()
