def is_triangle(a, b, c):
  if a + b > c and a + c > b and b + c > a:
    print("Yes")
  else:
    print("No")

def prompt_for_lengths():
  a = int(input("enter length of stick 1: "))
  b = int(input("enter length of stick 2: "))
  c = int(input("enter length of stick 3: "))
  
  is_triangle(a, b, c)

# example usage
prompt_for_lengths()