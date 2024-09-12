
def avoids(word, forbids):
  for c in forbids:
    if c in word:
      return False
  
  return True


def count_words(forbids):
  cnt = 0
  fin = open("words.txt")
  for line in fin:
    word = line.strip()
    if avoids(word, forbids):
      cnt += 1
  
  return cnt

def main():
  forbids = input("enter forbidden characters: ")
  cnt = count_words(forbids)
  print(f"number of words without forbidden characters: {cnt}")

main()