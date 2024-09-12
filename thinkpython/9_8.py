def is_palindrome(word):
  return word == word[::-1]

def check(i):
  if not is_palindrome(str(i)[2:]):
    return False

  if not is_palindrome(str(i + 1)[1:]):
    return False

  if not is_palindrome(str(i + 2)[1:5]):
    return False

  if not is_palindrome(str(i + 3)):
    return False
  
  return True

def main():
  for i in range(100000, 999999):
    if check(i):
      print(i)

main()
  