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

yesterday = np.datetime64('today') - np.timedelta64(1)
today     = np.datetime64('today')
tomorrow  = np.datetime64('today') + np.timedelta64(1)

print(yesterday)
print(today)
print(tomorrow)