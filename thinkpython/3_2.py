def do_twice(f, arg):
  f(arg)
  f(arg)

def print_spam():
  print('spam')

def print_twice(bruce):
  print(bruce)
  print(bruce)

def do_four(f, arg):
  do_twice(f, arg)
  do_twice(f, arg)

do_four(print_twice, 'spam')
