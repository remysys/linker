# 1. import the numpy package under the name np
import numpy as np

# 2. print the numpy version and the configuration
print(np.__version__)
np.show_config()

# 3. create a null vector of size 10
z = np.zeros(10)
print(z)

# 4. how to find the memory size of any array
z = np.zeros((10, 10))
print("%d bytes" % (z.size * z.itemsize))

# 5. how to get the documentation of the numpy add function from the command line
# python -c "import numpy; numpy.info(numpy.add)"

# 6. create a null vector of size 10 but the fifth value which is 1
z = np.zeros(10)
z[4] = 1
print(z) 

# 7. create a vector with values ranging from 10 to 49
z = np.arange(10, 50)
print(z)

# 8. reverse a vector (first element becomes last)
z = np.arange(10, 50)
z = z[::-1]
print(z)

# 9. create a 3x3 matrix with values ranging from 0 to 8
z = np.arange(9).reshape(3, 3)
print(z)

# 10. find indices of non-zero elements from [1,2,0,0,4,0]
nz = np.nonzero([1,2,0,0,4,0])
print(nz)

# 11. create a 3x3 identity matrix
z = np.eye(3)
# z = np.identity(3)
print(z)

# 12. create a 3x3x3 array with random values
z = np.random.random((3, 3, 3))
print(z)

# 13. create a 10x10 array with random values and find the minimum and maximum values
z = np.random.random((10, 10))
zmin, zmax = z.min(), z.max()
print(zmin, zmax)

# 14. create a random vector of size 30 and find the mean value

z = np.random.random(30)
m = z.mean()
print(m)

# 15. create a 2d array with 1 on the border and 0 inside
z = np.ones((10, 10))
z[1:-1, 1:-1] = 0
print(z)

# 16. how to add a border (filled with 0's) around an existing array
z = np.ones((5,5))
z = np.pad(z, pad_width = 1, mode = 'constant', constant_values = 0)
print(z)

# using fancy indexing
z[:, [0, -1]] = 0
z[[0, -1], :] = 0
print(z)

# 17. what is the result of the following expression
"""
0 * np.nan
np.nan == np.nan
np.inf > np.nan
np.nan - np.nan
np.nan in set([np.nan])
0.3 == 3 * 0.1
"""

print(0 * np.nan)
print(np.nan == np.nan)
print(np.inf > np.nan)
print(np.nan - np.nan)
print(np.nan in set([np.nan]))
print(0.3 == 3 * 0.1)

# 18. create a 5x5 matrix with values 1,2,3,4 just below the diagonal
z = np.diag(1 + np.arange(4), k = -1)
print(z)

# 19. create a 8x8 matrix and fill it with a checkerboard pattern

z = np.zeros((8, 8))
z[1::2, ::2] = 1  # set the odd columns of even rows to 1
z[::2, 1::2] = 1  # set the even columns of odd rows to 1
print(z)

# 20. consider a (6,7,8) shape array, what is the index (x,y,z) of the 100th element
print(np.unravel_index(99, (6,7,8)))

# or
x = 99 // (7 * 8)
y = (99 // 8) % 7
z = 99 % 8
print((x, y, z))

# 21. create a checkerboard 8x8 matrix using the tile function
z = np.tile(np.array([[0, 1], [1, 0]]), (4, 4))
print(z)

# 22. Normalize a 5x5 random matrix
z = np.random.random((5, 5))
z = z - np.mean(z) / np.std(z)
print(z)

# 23. create a custom dtype that describes a color as four unsigned bytes (RGBA)
color = np.dtype([("r", np.ubyte),
                  ("g", np.ubyte),
                  ("b", np.ubyte),
                  ("a", np.ubyte)])

colors = np.array([(255, 0, 0, 255),   # red
                   (0, 255, 0, 255),   # green
                   (0, 0, 255, 255)],  # blue
                  dtype=color)

# 24. multiply a 5x3 matrix by a 3x2 matrix (real matrix product)
z = np.dot(np.ones((5,3)), np.ones((3,2)))
print(z)

# alternative solution, in Python 3.5 and above
z = np.ones((5,3)) @ np.ones((3,2))
print(z)

# 25. given a 1D array, negate all elements which are between 3 and 8, in place
z = np.arange(10)
z[(3 < z) & (z < 8)] *= -1 
print(z)

# 26. what is the output of the following script
"""
print(sum(range(5), -1))
from numpy import *
print(sum(range(5), -1))
"""
print(sum(range(5), -1))
from numpy import *
print(sum(range(5), -1))

# 27. consider an integer vector z, which of these expressions are legal
"""
z**z
2 << z >> 2
z <- z
1j*z
z/1/1
z<z>z
"""
z = np.random.randint(0, 10, size = 5)
print(z)
print(z**z)
print(2 << z >> 2)
print(z <- z)
print(1j*z)
print(z/1/1)
# print(z<z>z) error

# 28. what are the result of the following expressions
"""
np.array(0) / np.array(0)
np.array(0) // np.array(0)
np.array([np.nan]).astype(int).astype(float)
"""

print(np.array(0) / np.array(0))
print(np.array(0) // np.array(0))
print(np.array([np.nan]).astype(int).astype(float))

# 29. how to round away from zero a float array
z = np.random.uniform(-10, +10, 10)
print(z)
print(np.copysign(np.ceil(np.abs(z)), z))

# more readable but less efficient
print(z)
print(np.where(z > 0, np.ceil(z), np.floor(z)))

# 30. how to find common values between two arrays
z1 = np.random.randint(0, 10, 10)
z2 = np.random.randint(0, 10, 10)
print(z1)
print(z2)
print(np.intersect1d(z1, z2))

# 31. how to ignore all numpy warnings (not recommended)
# suicide mode on
defaults = np.seterr(all = "ignore")
z = np.ones(1) / 0

# back to sanity
_ = np.seterr(**defaults)

# equivalently with a context manager
with np.errstate(all = "ignore"):
    np.arange(3) / 0

# 32. is the following expressions true
"""
np.sqrt(-1) == np.emath.sqrt(-1)
"""
print(np.sqrt(-1) == np.emath.sqrt(-1))

# 33. how to get the dates of yesterday, today and tomorrow?

yesterday = np.datetime64('today') - np.timedelta64(1, 'D')
today     = np.datetime64('today')
tomorrow  = np.datetime64('today') + np.timedelta64(1, 'D')

# 34. how to get all the dates corresponding to the month of July 2016
z = np.arange('2016-07', '2016-08', dtype='datetime64[D]')
print(z)

# 35. how to compute ((A+B)*(-A/2)) in place (without copy)
A = np.ones(3) * 1
B = np.ones(3) * 2
np.add(A, B, out = B)
np.divide(A, 2, out = A)
np.negative(A, out = A)
np.multiply(A, B, out = A)
print(A)

# 36. extract the integer part of a random array of positive numbers using 4 different methods
z = np.random.uniform(0, 10, 10)
print(z - z % 1)
print(z // 1)
print(np.floor(z))
print(z.astype(int))
print(np.trunc(z))

# 37. create a 5x5 matrix with row values ranging from 0 to 4
z = np.zeros((5, 5))
z += np.arange(5) 
print(z)

# without broadcasting
z = np.tile(np.arange(5), (5, 1))
print(z)

# 38. consider a generator function that generates 10 integers and use it to build an array
def generate():
  for x in range(10):
    yield x

z = np.fromiter(generate(), dtype = int, count = -1)
print(z)

# 39. create a vector of size 10 with values ranging from 0 to 1, both excluded
z = np.linspace(0, 1, 12)[1:-1]
print(z)

# 40. create a random vector of size 10 and sort it 
z = np.random.randint(0, 100, 10)
z.sort()
print(z)

# 41. how to sum a small array faster than np.sum
z = np.arange(10)
total_sum = np.add.reduce(z)
print(total_sum)

# 42. consider two random array A and B, check if they are equal
A = np.random.randint(0, 2, 5)
B = np.random.randint(0, 2, 5)
print(np.array_equal(A, B))

# 43. make an array immutable
z = np.zeros(10)
# z.flags.writeable = False
z[0] = 1
print(z)

# 44. consider a random 10x2 matrix representing cartesian coordinates, 
# convert them to polar coordinates
z = np.random.randint(0, 10, size=(10, 2))
x, y  = z[:, 0], z[:, 1]
print(x)
print(y)
r = np.sqrt((x ** 2) + (y ** 2))
t = np.arctan2(y, x)
print(r)
print(t)

# 45. create random vector of size 10 and replace the maximum value by 0
z = np.random.randint(0, 100, 10)
print(z)
i = np.argmax(z)
z[i] = 0
print(z)

# 46. create a structured array with x and y coordinates covering the [0,1]x[0,1] area
z = np.zeros((5, 5), dtype = [('x', float), ('y', float)])
t1, t2 = np.meshgrid(np.linspace(0, 1, 5), np.linspace(0, 1, 5))
z['x'], z['y'] = np.meshgrid(np.linspace(0, 1, 5), np.linspace(0, 1, 5))

# 47. given two arrays, X and Y, construct the Cauchy matrix C (Cij =1/(xi - yj))
X = np.random.randint(0, 10, 5)
Y = X + 0.5
C = 1.0 / np.subtract.outer(X, Y)
print(C)

# 48. print the minimum and maximum representable value for each numpy scalar type
for dtype in [np.int8, np.int16, np.int32, np.int64, np.uint8, np.uint16, np.uint32, np.uint64]:
   print(np.iinfo(dtype).min)
   print(np.iinfo(dtype).max)

for dtype in [np.float32, np.float64]:
   print(np.finfo(dtype).min)
   print(np.finfo(dtype).max)
   print(np.finfo(dtype).eps)

# 49. how to print all the values of an array
import sys
np.set_printoptions(threshold = sys.maxsize)
z = np.zeros((20, 20))
print(z)

# 50. how to find the closest value (to a given scalar) in a vector
z = np.arange(100)
v = np.random.uniform(0, 100)
index = np.abs(z - v).argmin()
print(z[index])

# 51. create a structured array representing a position (x,y) and a color (r,g,b)

color = np.dtype([("r", np.ubyte),
                  ("g", np.ubyte),
                  ("b", np.ubyte)])
position = np.dtype([("x", np.int32), ("y", np.int32)])

z = np.zeros((10, 10), dtype = [("color", color), ("position", position)])
print(z)

# or
z = np.zeros(10, [('color', [('r', np.int32), 
                             ('g', np.int32), 
                             ('b', np.int32)]), 
                  ('position', [('x', np.int32), 
                                ('y', np.int32)])
                 ])
print(z)

# 52. consider a random vector with shape (100, 2) representing coordinates, 
# find point by point distances

z = np.random.random((5, 2))
dist = np.linalg.norm(z[:, None] - z, axis = 2)
print(dist)

#53. how to convert a float (32 bits) array into an integer (32 bits) in place
z = (np.random.rand(10) * 100).astype(np.float32)
y = z.view(np.int32)
y[:] = z
print(y)

# 54. how to read the following file?
'''
1, 2, 3, 4, 5
6,  ,  , 7, 8
 ,  , 9,10,11
'''
# fake file
import io
s = io.StringIO('''1, 2, 3, 4, 5
                6,  ,  , 7, 8
                 ,  , 9, 10, 11
''')

z = np.genfromtxt(s, delimiter = ',', dtype = np.int32, filling_values = 0)
print(z)

# 55. what is the equivalent of enumerate for numpy arrays
z = np.arange(9).reshape(3, 3)
for index, value in np.ndenumerate(z):
  print(index, value)

for index in np.ndindex(z.shape):
  print(index, z[index])

# 56. generate a generic 2D Gaussian-like array
x = np.linspace(-1, 1, 100)
y = np.linspace(-1, 1, 100)
x, y = np.meshgrid(x, y)
sigma = 1.0
gaussian = np.exp(-(x**2 + y**2) / (2 * sigma**2))
print(gaussian)

# 57. how to randomly place p elements in a 2D array
shape = (10, 10)
p = 5
val = 1
z = np.zeros(shape)
total_elements = shape[0] * shape[1]
indices = np.random.choice(total_elements, size=p, replace=False)
np.put(z, indices, val)
print(z)

# 58. subtract the mean of each row of a matrix
z = np.random.randint(0, 10, (5, 5))
m = np.mean(z, axis=1, keepdims=True)
z = z - m
print(z)

# 59. how to sort an array by the nth column
n = 1
z = np.random.randint(0, 10, (3, 3))
print(z)
indices = z[:, n].argsort()
print(z[indices])

# 60. how to tell if a given 2D array has null columns
z = np.random.randint(0, 3, (5, 5))
print(z)

# null: 0 
print((~z.any(axis=0)).any())

# null: np.nan
z = np.array([[0, 1, np.nan],
             [3, 4, np.nan],
             [6, 7, np.nan]])

print(np.isnan(z).all(axis=0))

# 61. find the nearest value from a given value in an array
v = 100
z = np.random.randint(0, 10, (10, 10))
index = np.abs(z - v).argmin()
print(z)
print(index)
print(z.flat[index])

# 62. considering two arrays with shape (1,3) and (3,1), 
# how to compute their sum using an iterator

a = np.arange(3).reshape(3,1)
b = np.arange(3).reshape(1,3)
it = np.nditer([a, b, None])
for x, y, z in it:
  z[...] = x + y
print(it.operands[2])

# 63.create an array class that has a name attribute
class NamedArray:
  def __init__(self, array, name="no name"):
    self.array = np.array(array)
    self.name = name
  
  def __repr__(self):
    return f"NamedArray(name='{self.name}', array={self.array})"
  def __str__(self):
    return f"NamedArray(name='{self.name}', array={self.array})"

z = NamedArray(np.arange(10), "range 10")
print(z.name)
print(z)

# 64. Consider a given vector, how to add 1 to each element 
# indexed by a second vector (be careful with repeated indices)
z = np.zeros(10)
print(z)
indices = np.random.randint(0, len(z), 20)
np.add.at(z, indices, 1)
print(z)

# 65. how to accumulate elements of a vector (X) 
# to an array (F) based on an index list (I)

x = [1,2,3,4,5,6]
i = [1,3,9,3,4,1]
f = np.bincount(i, x)
print(f)

# 66. considering a (w,h,3) image of (dtype=ubyte), 
# compute the number of unique colors
w, h = 256, 256
image = np.random.randint(0, 8, (w, h, 3)).astype(np.ubyte)
image2D = image.reshape(-1, 3)
rgbs = np.unique(image2D, axis=0)
n = len(rgbs)
print(n)

# 67. considering a four dimensions array, 
# how to get sum over the last two axis at once
z = np.random.randint(0, 2, (3, 3, 3, 3))
r = z.sum(axis=(-2, -1))
print(r)

# 68. considering a one-dimensional vector D, 
# how to compute means of subsets of D using a vector S 
# of same size describing subset indices

D = np.random.randint(0, 10, 100)
S = np.random.randint(0, 5, 100)
D_sum = np.bincount(S, weights=D)
S_count = np.bincount(S)
r = D_sum / S_count
print(r)

# pandas solution
import pandas as pd
print(pd.Series(D).groupby(S).mean())


# 69. how to get the diagonal of a dot product
a = np.random.randint(0, 5, (5, 5))
b = np.random.randint(0, 5, (5, 5))
p = np.dot(a, b)
print(p)

# slow version
z = np.diag(p)
print(z)

# fast version
z = np.sum(a * b.T, axis=1)
print(z)

# faster version
z = np.einsum("ij,ji->i", a, b)
print(z)

# 70. consider the vector [1, 2, 3, 4, 5], 
# how to build a new vector with 3 consecutive zeros interleaved between each value

z = np.array([1, 2, 3, 4, 5])
z_len = len(z)
nz = 3
z0 = np.zeros(z_len + (z_len - 1) * nz)
z0[::nz + 1] = z
print(z0)

# 71. consider an array of dimension (5,5,3), 
# how to mulitply it by an array with dimensions (5,5)
a = np.ones((5, 5, 3))
b = np.ones((5, 5)) * 2
z = a * b[:, :, None]
print(z)

# 72. how to swap two rows of an array? 
a = np.arange(25).reshape(5,5)
a[[0,1]] = a[[1,0]]
print(a)

# 73. consider a set of 10 triplets describing 10 triangles (with shared vertices), 
# find the set of unique line segments composing all the triangles

triangles = np.random.randint(0, 5, (10, 3))

t = np.roll(triangles.repeat(2, axis=1), -1, axis=1).reshape(30, 2)
t = np.sort(t, axis=1)
v = t.view(dtype = [("p0", t.dtype), ("p1", t.dtype)])
z = np.unique(v)
print(z)

# 74. given a sorted array C that corresponds to a bincount, 
# how to produce an array A such that np.bincount(A) == C

c = np.sort(np.random.randint(0, 3, 10))
a = np.repeat(np.arange(len(c)), c)
print(c)
print(a)
print(np.bincount(a))

# 75. how to compute averages using a sliding window over an array
z = np.random.randint(0, 10, 10)
s = np.cumsum(z)
n = 3
s[n:] = s[n:] - s[:-n]
r = s[n-1:] / n
print(z)
print(s)
print(r)

# 76. consider a one-dimensional array Z, build a two-dimensional array 
# whose first row is (Z[0],Z[1],Z[2]) 
# and each subsequent row is shifted by 1 (last row should be (Z[-3],Z[-2],Z[-1])

import numpy as np
t = np.arange(0, 10)
z = np.array([t[i: i+3] for i in range(len(t) - 2)])
print(z)

# 77. how to negate a boolean, or to change the sign of a float inplace
z = np.random.randint(0, 2, 10)
print(z)
np.logical_not(z, out=z)
print(z)

z = np.random.uniform(-1.0, 1.0, 3)
print(z)
np.negative(z, out=z)
print(z)

# 78. consider 2 sets of points P0,P1 describing lines (2d) and a point p, 
# how to compute distance from p to each line i (P0[i],P1[i])

p0 = np.random.randint(-5, 5, (3, 2))
p1 = np.random.randint(-5, 5, (3, 2))
p = np.array([0, 1])
# p = np.random.randint(-5, 5, (1, 2))
#p0 = np.array([[0, 0], [0, -1]])
#p1 = np.array([[1, 0], [1, -1]])
#p = np.array([0, 1])
d = np.abs(np.cross(p1 - p0, p - p0))/ np.linalg.norm(p1 - p0, axis = 1)
print(p0)
print(p1)
print(p)
print(d)

# 79. consider 2 sets of points P0,P1 describing lines (2d) 
# and a set of points P, how to compute distance from each point j (P[j]) 
# to each line i (P0[i],P1[i])
def dist(p0, p1, p):
  return np.abs(np.cross(p1 - p0, p - p0))/ np.linalg.norm(p1 - p0, axis = 1)

p0 = np.random.randint(-5, 5, (3, 2))
p1 = np.random.randint(-5, 5, (3, 2))
p = np.random.randint(-5, 5, (2, 2))

#p0 = np.array([[0, 0], [0, -1]])
#p1 = np.array([[1, 0], [1, -1]])
#p = np.array([[0, 1], [1, 1]])

print(np.array([dist(p0, p1, p_i) for p_i in p]))


# 80. consider an arbitrary array, write a function that extract a 
# subpart with a fixed shape and centered on a given element 
# (pad with a fill value when necessary)
z = np.arange(0, 100). reshape(10, 10)

center = (5, 5) 
shape = (3, 3)
fill = 0

c = np.array(list(center))
s = np.array(list(shape))
zs = np.array(list(z.shape))

start = c - s // 2
end = c + s // 2 + 1

start = np.maximum(start, 0)
end = np.minimum(end, zs - 1)
t = tuple(slice(s, e) for s, e in zip(start, end))
subpart = z[t]
print(subpart)

# 81. consider an array Z = [1,2,3,4,5,6,7,8,9,10,11,12,13,14], 
# how to generate an array R = [[1,2,3,4], [2,3,4,5], [3,4,5,6], ..., [11,12,13,14]]?

z = np.arange(1, 15)
print(np.array([z[i : i+4] for i in range(len(z) - 3)]))

# 82. compute a matrix rank
z = np.random.randint(0, 10, (10, 10))
rank = np.linalg.matrix_rank(z)
print(rank)

# 83. how to find the most frequent value in an array

z = np.random.randint(0, 10, 100)
r = np.bincount(z)
print(r)
print(r.argmax())

# 84. extract all the contiguous 3x3 blocks from a random 10x10 matrix

z = np.arange(100).reshape(10, 10)
blocks = np.array([z[i:i+3, j:j+3] for i in range(8) for j in range(8)])
print(blocks)

# 85. create a 2D array subclass such that Z[i,j] == Z[j,i]
class Symetric(np.ndarray):
  def __setitem__(self, index, val):
    i, j = index
    super().__setitem__((i, j), val)
    super().__setitem__((j, i), val)

def symetric(z):
  return (z + z.T - np.diag(z.diagonal())).view(Symetric)

z = np.random.randint(0, 10, (5, 5))
print(z)
s = symetric(z)
s[2,3] = 42
print(s)

# 86. consider a set of p matrices with shape (n,n) and a set of p vectors with shape (n,1). 
# How to compute the sum of of the p matrix products at once? (result has shape (n,1))
p = 10
n = 5

m = np.ones((p, n, n)) # matrices
v = np.ones((p, n, 1)) # vectors
z = np.tensordot(m, v, axes=[[0, 2], [0, 1]])
print(z)

# 87. consider a 16x16 array, how to get the block-sum (block size is 4x4)
z = np.ones((16, 16))
n = 4
t = np.add.reduceat(z, np.arange(0, z.shape[0], n), axis=0)
s = np.add.reduceat(t, np.arange(0, z.shape[1], n), axis=1)
print(s)

# 88. how to implement the Game of Life using numpy arrays
# 89. how to get the n largest values of an array
z = np.arange(10000)
np.random.shuffle(z)
n = 3
print(np.sort(z)[-n:])
print(z[np.argsort(z)[-n:]])
print(z[np.argpartition(-z, n)[:n]])

# 90. given an arbitrary number of vectors, 
# build the cartesian product (every combinations of every item)
arrays = np.array(np.arange(12)).reshape(3, 4)
shape = [len(x) for x in arrays]
grid = np.indices(shape)
grid = grid.reshape(len(arrays), -1).T

for n, a in enumerate(arrays):
  grid[:, n] = arrays[n][grid[:, n]]

print(grid)

# 91. how to create a record array from a regular array

z = np.array([("Hello", 2.5, 3),
              ("World", 3.6, 2)])
r = np.core.records.fromarrays(z.T,
                               names='col1, col2, col3',
                               formats = 'S8, f8, i8')

# 92. consider a large vector Z, compute Z to the power of 3 using 3 different methods

x = np.random.rand(int(5e7))

np.power(x, 3)
x*x*x
np.einsum('i,i,i->i', x, x, x)

# 93. consider two arrays A and B of shape (8,3) and (2,2). 
# how to find rows of A that contain elements of each row of B regardless 
# of the order of the elements in B?

a = np.random.randint(0,3,(8,3))
b = np.random.randint(0,2,(2,2))

c = (a[..., np.newaxis, np.newaxis] == b)
rows = np.where(c.any(1).all(1).all(1))[0]
print(a)
print(b)
print(rows)

# 94. considering a 10x3 matrix, extract rows with unequal values (e.g. [2,2,3])

z = np.random.randint(0, 3, (10, 3))
print(z)
e = np.all(z[:, :-1] == z[:, 1:], axis=1)
u = z[~e]
print("unequal rows:\n", u)

# 95. convert a vector of ints into a matrix binary representation
v = np.arange(10)
t = 2**np.arange(8)
m = (v.reshape(-1, 1) & t != 0).astype(np.int32)
z = m[:, ::-1]
print(v)
print(m)
print(z)

# 96. given a two dimensional array, how to extract unique rows

z = np.random.randint(0, 2, (10, 3))
print(z)
u = np.unique(z, axis=0)
print("unique rows:\n", u)

# 97. considering 2 vectors A & B, write the einsum equivalent of inner, outer, 
# sum, and mul function
# make sure to read: http://ajcr.net/Basic-guide-to-einsum/

a = np.random.randint(0, 1, 10)
b = np.random.randint(0, 1, 10)

np.einsum('i->', a)         # np.sum(a)
np.einsum('i,i->i', a, b)   # a * b
np.einsum('i,i', a, b)      # np.inner(a, b)
np.einsum('i,j->ij', a, b)  # np.outer(a, b) 

# 98. considering a path described by two vectors (X,Y), 
# how to sample it using equidistant samples

# 99. given an integer n and a 2D array X, select from X the rows 
# which can be interpreted as draws from a multinomial distribution with n degrees, 
# i.e., the rows which only contain integers and which sum to n

x = np.random.randint(0, 2, (20, 3))
n = 3

is_int = np.all(x == x.astype(int), axis=1)
is_sum_n = np.sum(x, axis=1) == n
mask = np.logical_and(is_int, is_sum_n)
z = x[mask]
print(z)

# 100. compute bootstrapped 95% confidence intervals for the mean of a 1D array X 
# (i.e., resample the elements of an array with replacement N times, 
# compute the mean of each sample, 
# and then compute percentiles over the means).

z = np.random.randint(0, 10, 100)
print("z mean:", z.mean())
n = 1000
samples = np.random.randint(0, z.size, (n, z.size))
means = z[samples].mean(axis=1)
confint = np.percentile(means, [2.5, 97.5])
print(confint)