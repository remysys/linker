def is_palindrome(word):
  return word == word[::-1]

print(is_palindrome('allen'))
print(is_palindrome('bob'))
print(is_palindrome('otto'))
print(is_palindrome('redivider'))
print(is_palindrome('hi'))