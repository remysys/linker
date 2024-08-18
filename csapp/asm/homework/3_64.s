# long A[R][S][T];
# 设L为数组元素的大小, base表示数组的起始地址
# &A[i][j][k] = base + L(i * S * T + j * T + k)


# long A[R][S][T];

# long store_ele(long i, long j, long k, long *dest) {
#   *dest = A[i][j][k];
#   return sizeof(A);
# }

# long store_ele(long i, long j, long k, long *dest)
# i in %rdi, j in %rsi, k in %rdx, dest in %rcx
store_ele:
  leaq (%rsi,%rsi,2), %rax      # rax = 3*j
  leaq (%rsi,%rax,4), %rax      # rax = 13*j
  movq %rdi, %rsi               # rsi = i
  salq $6, %rsi                 # rsi = 64*i
  addq %rsi, %rdi               # rdi = 65*i
  addq %rax, %rdi               # rdi = 65*i + 13*j
  addq %rdi, %rdx               # rdx = 65*i + 13*j + k
  movq A(,%rdx,8), %rax         # rax = A[(65*i + 13*j + k)]
  movq %rax, (%rcx)             # *dest = A[(65*i + 13*j + k)]
  movl $3640, %eax              # 8*R*S*T == 3640
  ret            

# &A[i][j][k] = base + L(i * S * T + j * T + k)
# &A[i][j][k] = base + L(65*i + 13*j + k)
# => 
# L: 8
# T: 13
# S: 5

# 8*R*S*T == 3640 
# =>
# R = 7