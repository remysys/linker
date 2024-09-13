import time

def make_word_list1():
  t = []
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    t.append(word)
  
  return t

def make_word_list2():
  t = []
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    t = t + [word]      # try t += [word]
  
  return t

def main():
  start_time = time.time()
  t = make_word_list1()
  elapsed_time = time.time() - start_time

  print(len(t))
  print(t[:10])
  print(f"{elapsed_time:.3f} seconds")

  start_time = time.time()
  t = make_word_list2()
  elapsed_time = time.time() - start_time

  print(len(t))
  print(t[:10])
  print(f"{elapsed_time:.3f} seconds")

main()