import math

def eval_loop():
  last = None
  while True:
    expr = input(">>> ")
    if expr == "done":
      return last

    last = eval(expr)
    print(last)
    
eval_loop()

