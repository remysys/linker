
def make_word_dict():
  d = dict()
  fin = open('words.txt')
  for line in fin:
    word = line.strip().lower()
    d[word] = None
  
  for letter in ['a', 'i']:
    d[letter] = letter
  
  return d

def children(word, word_dict):
  res = []
  for i in range(len(word)):
    child = word[:i] + word[i+1:]
    if child in word_dict:
      res.append(child)
  return res

"""memo is a dictionary that maps from each word that is known
to be reducible to a list of its reducible children.  it starts
with the empty string."""

memo = {}

def is_reducible(word, word_dict):
  """if word is reducible, returns a list of its reducible children.
  also adds an entry to the memo dictionary.
  a string is reducible if it has at least one child that is 
  reducible. the empty string is also reducible.
  """
    
  if word in memo:
    return memo[word]

  res = []

  if len(word) == 1: 
    if word in word_dict:
      res.append('')
      memo[word] = res
      return res
    else:
      return res

  for child in children(word, word_dict):
    if is_reducible(child, word_dict):
      res.append(child)

  memo[word] = res
  return res

def all_reducible(word_dict):
  """checks all words in the word_dict; returns a list reducible ones."""
  res = []
  for word in word_dict:
    if is_reducible(word, word_dict):
      res.append(word)
  
  return res

def print_seq(word):
  """prints the sequence of words that reduces this word to the empty string.
  if there is more than one choice, it chooses the first.
  """

  if len(word) == 0:
    return 
  print(word, end = ' ')
  t = is_reducible(word, word_dict)
  print_seq(t[0])


def print_longest_words(word_dict):

  words = all_reducible(word_dict)
  t = []
  for word in words:
    t.append((len(word), word))
  t.sort(reverse = True)

  # print the longest 5 words
  for _, word in t[0:5]:
    print_seq(word)
    print('\n')

if __name__ == '__main__':
  word_dict = make_word_dict()
  print_longest_words(word_dict)
