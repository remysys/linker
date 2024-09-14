def signature(word):
  t = list(word)
  t.sort()
  return ''.join(t)

def all_anagrams(filename):
  d = {}
  fin = open(filename)
  for line in fin:
    word = line.strip().lower()
    t = signature(word)

    if t not in d:
      d[t] = [word]
    else:
      d[t].append(word)

  return d

def word_distance(word1, word2):
  assert len(word1) == len(word2)

  count = 0
  for c1, c2 in zip(word1, word2):
    if c1 != c2:
      count += 1
  return count

def metathesis_pairs(d):
  for anagrams in d.values():
    for word1 in anagrams:
      for word2 in anagrams:
        if word1 < word2 and word_distance(word1, word2) == 2:
          print(word1, word2)


if __name__ == '__main__':
  d = all_anagrams('words.txt')
  metathesis_pairs(d)