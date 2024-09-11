def check_fermat(a, b, c, n):
  if n > 2 and (a**n + b**n == c**n):
    print("Holy smokes, Fermat was wrong!")
  else:
    print("No, that doesn’t work.")

def prompt_for_values():
  a = int(input("enter value for a: "))
  b = int(input("enter value for b: "))
  c = int(input("enter value for c: "))
  n = int(input("enter value for n: "))
    
  check_fermat(a, b, c, n)

# example usage
prompt_for_values()