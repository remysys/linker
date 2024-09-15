import os

def walk(dirname):
  names = []

  for name in os.listdir(dirname):
    path = os.path.join(dirname, name)

    if os.path.isfile(path):
      names.append(path)
    else:
      names.extend(walk(path))
  
  return names

def pipe(cmd):
  """runs a command in a subprocess
  cmd: string unix command
  returns (res, stat), the output of the subprocess and the exit status
  """
  fp = os.popen(cmd)
  res = fp.read()
  stat = fp.close()
  assert stat is None
  return res, stat

def md5sum(filename):

  cmd = 'md5sum ' + filename
  return pipe(cmd)

def diff(name1, name2):

  cmd = 'diff %s %s' % (name1, name2)
  return pipe(cmd)

def compute_checksums(dirname, suffix):
  names = walk(dirname)

  d = {}

  for name in names:
    if name.endswith(suffix):
      res, stat = md5sum(name)
      checksum, _ = res.split()

      if checksum in d:
        d[checksum].append(name)
      else:
        d[checksum] = [name]

  return d

def check_pairs(names):
  for name1 in names:
    for name2 in names:
      if name1 < name2:
        res, stat = diff(name1, name2)
        if res:
          return False
  
  return True

def print_dups(d):
  for key, names in d.items():
    if len(names) > 1:
      for name in names:
        print(name, end = ' ')
      print()

      if check_pairs(names):
        print('and they are identical.')

if __name__ == '__main__':
  d = compute_checksums(dirname = '.', suffix = '.py')
  print_dups(d)