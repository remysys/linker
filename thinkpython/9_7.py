def is_triple_double(word):
  i = 0
  count = 0

  while i < len(word) - 1:
    if word[i] == word[i + 1]:
      count += 1
      i += 2
    else:
      count = 0
      i += 1
    
    if count == 3:
      return True
  
  return False

def count_words():
  cnt = 0
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    if is_triple_double(word):
      print(word)
      cnt += 1
  
  return cnt

cnt = count_words()
print(f"number of triple double words: {cnt}")
