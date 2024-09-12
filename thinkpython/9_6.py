def is_abecedarian(word):
  i = 0;
  while i < len(word) - 1:
    if word[i] >= word[i + 1]:
      return False
    else:
      i += 1
  
  return True

def count_words():
  cnt = 0
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    if is_abecedarian(word):
      print(word)
      cnt += 1
  
  return cnt

def main():
  cnt = count_words()
  print(f"number of abecedarian words: {cnt}")

main()