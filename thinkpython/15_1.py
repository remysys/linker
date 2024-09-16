#!/usr/bin/env python3
import copy
import math

class Point:
  """attr: x, y"""

def print_point(p):
  print('(%g, %g)' % (p.x, p.y))

def distance_between_points(p1, p2):
  dx = p1.x - p2.x
  dy = p1.y - p2.y
  dist = math.sqrt(dx ** 2 + dy ** 2)
  return dist

class Rectangle:
  """attr: width, height, corner"""

class Circle:
  """attr: center, radius"""

def point_in_circle(circle, point):
  d = distance_between_points(circle.center, point)
  
  return d <= circle.radius

def rect_in_circle(circle, rect):
  
  p = copy.copy(rect.corner)
  print_point(p)
  if not point_in_circle(circle, p):
    return False

  p.x += rect.width
  print_point(p)
  if not point_in_circle(circle, p):
    return False
  
  p.y += rect.height
  print_point(p)
  if not point_in_circle(circle, p):
    return False
  
  p.x -= rect.width
  print_point(p)
  if not point_in_circle(circle, p):
    return False
  
  return True

def rect_circle_overlap(circle, rect):

  p = copy.copy(rect.corner)
  print_point(p)
  if point_in_circle(circle, p):
    return True

  p.x += rect.width
  print_point(p)
  if point_in_circle(circle, p):
    return True
  
  p.y += rect.height
  print_point(p)
  if point_in_circle(circle, p):
    return True
  
  p.x -= rect.width
  print_point(p)
  if point_in_circle(circle, p):
    return True
  
  return False

if __name__ == '__main__':
  circle = Circle()
  circle.center = Point()
  circle.center.x = 150.0
  circle.center.y = 100.0
  circle.radius = 75.0

  print(circle.center.x)
  print(circle.center.y)
  print(circle.radius)

  box = Rectangle()
  box.width = 100.0
  box.height = 200.0
  box.corner = Point()
  box.corner.x = 50.0
  box.corner.y = 50.0

  print(box.corner.x)
  print(box.corner.y)

  print(point_in_circle(circle, box.corner))
  print(rect_in_circle(circle, box))
  print(rect_circle_overlap(circle, box))


  
