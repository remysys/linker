# **
# the following code computes the 128-bit product of two 64-bit signed value x
# and y and stores the result in memory.
#
# typedef __int128 int128_t;
#
# void store_prod(int128_t *dest, int64_t x, int64_t y) {
#     *dest = x * (int128_t) y;
# }
#
# gcc generates the following assembly code implementing the computation:
#
# store_prod:
#   movq    %rdx, %rax
#   cqto
#   movq    %rsi, %rcx
#   sarq    $63, %rcx
#   imulq   %rax, %rcx
#   imulq   %rsi, %rdx
#   addq    %rdx, %rcx
#   mulq    %rsi
#   addq    %rcx, %rdx
#   movq    %rax, (%rdi)
#   movq    %rdx, 8(%rdi)
#   ret
#
#     this code uses three multiplications for the multiprecision arithmetic
# required to implement 128-bit arithmetic on a 64-bit machine. Describe the 
# algorithm used to compute the product, and annotate the assembly code to show
# how it realizes your algorithm. Hint: When extending arguments of x and y to
# 128 bits, they can be rewritten as x = 2^64 * xh + xl and y = 2^64 * yh + yl,
# where xh, xl, yh, and yl are 64-bit values. Similarly, the 128-bit product can
# be written as p = 2^64 * ph + pl, where ph and pl are 64-bit values. Show how
# the code computes the values of ph and pl in terms of xh, xl, yh, yl.

store_prod:             # store_prod(rdi, rsi, rdx)
  movq    %rdx, %rax    # %rax = yl
  cqto                  # %rdx = %rdx = (-1)y_63 = yh
  
  # x >> 63, if x == 1, %rcx = -1; if x_63 == 0, %rcx = 0

  movq    %rsi, %rcx    # %rcx = (-1)x_63 = xh
  sarq    $63, %rcx     
  imulq   %rax, %rcx    # %rcx = yl * xh
  imulq   %rsi, %rdx    # %rdx = xl * yh
  addq    %rdx, %rcx    # %rcx = yl * xh + xl * yh

  # %rax = xl * yl % 2^64
  # %rdx = xl * yl / 2^64
  mulq    %rsi          

  addq    %rcx, %rdx    # %rdx = yl * xh + xl * yh + xl * yl / 2^64
  movq    %rax, (%rdi)  # *(rdi + 0) = xl * yl % 2^64
  movq    %rdx, 8(%rdi) # *(rdi + 8) = yl * xh + xl * yh + xl * yl / 2^64
  ret

# in the above code, rsi is xl, rcx is xh, rax is yl, rdx is yh.
#   x * y                                                   (mod 2^128)
# = (2^64 * xh + xl) * (2^64 * yh + yl)                     (mod 2^128)
# = 2^128 * xh * yh + 2^64 * (xh * yl + xl * yh) + xl * yl  (mod 2^128)
# = 2^64 * (xh * yl + xl * yh) + xl * yl
# = 2^64 * (xh * yl + xl * yh + xl * yl / 2^64) + xl * yl % 2^64
#
# and according to the Equation 2.7 (P94 in English ver or P67 Chinese translate
# ver), the result of low 64 bits can be calculated through unsigned
# multiplication and a modulus, so one mulq is enough to produce both xl * yl /
# 2^64 and xl * yl % 2^64, which will be saved in rdx and rax by mulq.