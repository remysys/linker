
def uses_only(word, str):
  for c in word:
    if c not in str:
      return False
  
  return True

def print_words():
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    if uses_only(word, "acefhlo"):
      print(word)

print_words()