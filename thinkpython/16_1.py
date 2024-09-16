#!/usr/bin/env python3

class Time:
  """attr: hour, minute, second"""

def print_time(t):
  print('%.2d:%.2d:%.2d' % (t.hour, t.minute, t.second))


def int_to_time(seconds):
  time = Time()
  minutes, time.second = divmod(seconds, 60)
  time.hour, time.minute = divmod(minutes, 60)
  return time

def time_to_int(time):
  minutes = time.hour * 60 + time.minute
  seconds = minutes * 60 + time.second
  return seconds

def valid_time(time):
  if time.hour < 0 or time.minute < 0 or time.second < 0:
    return False
  if time.minute >= 60 or time.second >= 60:
    return False
  return True

def mul_time(t, factor):
  assert valid_time(t)
  seconds = time_to_int(t) * factor
  return int_to_time(seconds)

if __name__ == '__main__':
  race_time = Time()
  race_time.hour = 1
  race_time.minute = 34
  race_time.second = 5
  
  distance = 13.1       # miles
  pace = mul_time(race_time, 1/distance)
  print('time per mile', end=' ')
  print_time(pace)
  