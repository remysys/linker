
#!/usr/bin/env python3

from datetime import datetime

def main():
  print("today's date and the day of the week:")
  today = datetime.today()
  print(today)
  print(today.strftime("%A"))


  print('your next birthday and how far away it is:')
  # s = input('enter you birthday in mm/dd/yyyy format: ')
  s = '5/11/1967'
  bday = datetime.strptime(s, '%m/%d/%Y')

  next_bday = bday.replace(year = today.year)
  if next_bday < today:
    next_bday = next_bday.replace(year = today.year + 1)
  print(next_bday)
  util_next_day = next_bday - today
  print(util_next_day)

  print('your current age:')
  last_bday = next_bday.replace(year = next_bday.year - 1)
  age = last_bday.year - bday.year
  print(age)

  print('for people born on these dates:')
  bday1 = datetime(day = 11, month = 5, year = 1967)
  bday2 = datetime(day = 11, month = 10, year = 2003)
  print(bday1)
  print(bday2)

  print('double day is')
  d1 = min(bday1, bday2)
  d2 = max(bday1, bday2)
  dd = d2 + (d2 - d1)
  print(dd)

  n = 3
  print('%d day is' % n)
  nd = d2 + (d2 - d1) / (n - 1)
  print(nd)

if __name__ == '__main__':
  main()