
def has_no_e(word):
  return 'e' not in word

def print_words_and_ratio():
  total = 0;
  cnt = 0

  fin = open("words.txt")
  for line in fin:
    total += 1
    word = line.strip()
    if has_no_e(word):
      print(word)
      cnt += 1

  ratio = cnt / total if total > 0 else 0
  print(f"proportion of words without 'e': {ratio:.2%}")

print_words_and_ratio()