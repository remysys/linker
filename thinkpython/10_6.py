def is_anagram(word1, word2):
  return sorted(word1) == sorted(word2)

print(is_anagram("remy", "yemr"))
print(is_anagram("remy", "yemi"))

