def uses_all(word, str):
  for c in str:
    if c not in word:
      return False
  
  return True

def count_words(str):
  cnt = 0
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    if uses_all(word, str):
      cnt += 1
  
  return cnt

def main():
  cnt = count_words("aeiou")
  print(f"number of words containing all vowels: {cnt}")

  cnt = count_words("aeiouy")
  print(f"number of words containing 'aeiouy': {cnt}")


main()