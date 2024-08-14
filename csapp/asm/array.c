/* 
 * compute i,k of fixed matrix product 
 * gcc -O1 -S array.c
 */

#define N 16
typedef int fix_matrix[N][N];

int fix_prod_ele(fix_matrix A, fix_matrix B, long i, long k) {
  long j;
  int result = 0;

  for (j = 0; j < N; j++)
    result += A[i][j] * B[j][k];
  
  return result;
}


/* compute i,k of variable matrix product */

int var_prod_ele(long n, int A[n][n], int B[n][n], long i, long k) {
  long j;
  int result = 0;

  for (j = 0; j < n; j++)
    result += A[i][j] * B[j][k];

  return result;
}