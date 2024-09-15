#!/usr/bin/env python3

import sys
import string
import matplotlib.pyplot as plt

def process_line(line, hist):
  line = line.replace('-', ' ')
  strippables = string.punctuation + string.whitespace
  for word in line.split():
    word = word.strip(strippables).lower()
    hist[word] = hist.get(word, 0) + 1

def skip_header(fp):
  for line in fp:
    if line.startswith('*** START OF THIS'):
      break

def process_file(filename):
  hist = dict()
  fp = open(filename)

  skip_header(fp)

  for line in fp:
    if line.startswith('*** END OF THIS'):
      break
    
    process_line(line, hist)
  
  return hist 

def rank_freq(hist):
  # sort the list of frequencies in decreasing order
  freqs = list(hist.values())
  freqs.sort(reverse = True)

  # enumerate the ranks and frequencies
  rf = [(r + 1, f) for r, f in enumerate(freqs)]
  return rf

def print_ranks(hist):
  for r, f in rank_freq(hist):
    print(r, f)

def plot_ranks(hist, scale ='log'):
  t = rank_freq(hist)
  rs, fs = zip(*t)

  plt.clf()
  plt.xscale(scale)
  plt.yscale(scale)
  plt.title('zipf plot')
  plt.xlabel('rank')
  plt.ylabel('frequency')
  plt.plot(rs, fs, 'r-', linewidth = 3)
  plt.savefig('output.png')
  # plt.show()

def main(script, filename = 'emma.txt', flag = 'print'):
  hist = process_file(filename)

  # either print the results or plot them
  if flag == 'print':
    print_ranks(hist)
  elif flag == 'plot':
    plot_ranks(hist)
  else:
    print('usage: script.py filename [print|plot]')

if __name__ == '__main__':
  main(*sys.argv)