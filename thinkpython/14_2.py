#!/usr/bin/env python3

import shelve

from anagram_sets import all_anagrams, signature

def store_anagrams(filename, anagram_map):
  shelf = shelve.open(filename, 'c')

  for word, word_list in anagram_map.items():
    shelf[word] = word_list
  
  shelf.close()

def read_anagrams(filename, word):
  shelf = shelve.open(filename)
  sig = signature(word)

  try:
    return shelf[sig]
  except KeyError:
    return []

if __name__ == '__main__':
  anagram_map = all_anagrams('words.txt')
  store_anagrams('anagrams.db', anagram_map)
  print(read_anagrams('anagrams.db', 'palest'))
  
