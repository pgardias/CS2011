// pmgardias - Przemek Gardias

/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a bdiagIndexk size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
	// 32 x 32 matrix
	if (N == 32) {
		int i, j, a, b, temp, diagIndex;
		int blockSize = 8;
		for (i = 0; i < N; i += blockSize) {
			for (j = 0; j < M; j += blockSize) {
				for (b = i; b < i + blockSize; b++) {
					for (a = j; a < j + blockSize; a++) {
						if (a == b) {
							temp = A[b][a];
							diagIndex = b;
						}
						else {
							B[a][b] = A[b][a];
						}
					}
					if (i == j) {
						B[diagIndex][diagIndex] = temp;
					}
				}
			}
		}
	} else if (N == 64) { // 64 x 64 matrix
		// Init storage vars
		int storage1, storage2, storage3, storage4, storage5, storage6, storage7, storage8;
		for (int i = 0; i < 64; i += 8) {
			for (int j = 0; j < 64; j += 8) {
				for (int k = 0; k < 4; k++) {
					storage1 = A[i + k][j + 0];
					storage2 = A[i + k][j + 1];
					storage3 = A[i + k][j + 2];
					storage4 = A[i + k][j + 3];
					storage5 = A[i + k][j + 4];
					storage6 = A[i + k][j + 5];
					storage7 = A[i + k][j + 6];
					storage8 = A[i + k][j + 7];

					B[j + 0][i + k + 0] = storage1;
					B[j + 0][i + k + 4] = storage6;
					B[j + 1][i + k + 0] = storage2;
					B[j + 1][i + k + 4] = storage7;
					B[j + 2][i + k + 0] = storage3;
					B[j + 2][i + k + 4] = storage8;
					B[j + 3][i + k + 0] = storage4;
					B[j + 3][i + k + 4] = storage5;
				}

				// Move stored elements into correct positions
				storage1 = A[i + 4][j + 4];
				storage2 = A[i + 5][j + 4];
				storage3 = A[i + 6][j + 4];
				storage4 = A[i + 7][j + 4];
				storage5 = A[i + 4][j + 3];
				storage6 = A[i + 5][j + 3];
				storage7 = A[i + 6][j + 3];
				storage8 = A[i + 7][j + 3];

				B[j + 4][i + 0] = B[j + 3][i + 4];
				B[j + 4][i + 4] = storage1;
				B[j + 3][i + 4] = storage5;
				B[j + 4][i + 1] = B[j + 3][i + 5];
				B[j + 4][i + 5] = storage2;
				B[j + 3][i + 5] = storage6;
				B[j + 4][i + 2] = B[j + 3][i + 6];
				B[j + 4][i + 6] = storage3;
				B[j + 3][i + 6] = storage7;
				B[j + 4][i + 3] = B[j + 3][i + 7];
				B[j + 4][i + 7] = storage4;
				B[j + 3][i + 7] = storage8;

				for (int k = 0; k < 3; k++) {
					storage1 = A[i + 4][j + 5 + k];
					storage2 = A[i + 5][j + 5 + k];
					storage3 = A[i + 6][j + 5 + k];
					storage4 = A[i + 7][j + 5 + k];
					storage5 = A[i + 4][j + k];
					storage6 = A[i + 5][j + k];
					storage7 = A[i + 6][j + k];
					storage8 = A[i + 7][j + k];

					B[j + 5 + k][i + 0] = B[j + k][i + 4];
					B[j + 5 + k][i + 4] = storage1;
					B[j + k][i + 4] = storage5;
					B[j + 5 + k][i + 1] = B[j + k][i + 5];
					B[j + 5 + k][i + 5] = storage2;
					B[j + k][i + 5] = storage6;
					B[j + 5 + k][i + 2] = B[j + k][i + 6];
					B[j + 5 + k][i + 6] = storage3;
					B[j + k][i + 6] = storage7;
					B[j + 5 + k][i + 3] = B[j + k][i + 7];
					B[j + 5 + k][i + 7] = storage4;
					B[j + k][i + 7] = storage8;
				}
			}
		}
	} else { // All other matrix sizes
		int temp, diagIndex;
		int blockSize = 16;
		for (int i = 0; i < N; i += blockSize) {
			for (int j = 0; j < M; j += blockSize) {
				for (int b = i; ((b < i + blockSize) && (b < N)); b++) {
					for (int a = j; ((a < j + blockSize) && (a < M)); a++) {
						if (a == b) {
							temp = A[b][a];
							diagIndex = b;
						} else {
							B[a][b] = A[b][a];
						}
					}
					if (i == j) {
						B[diagIndex][diagIndex] = temp;
					}
				}
			}
		}
	}
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple j-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, temp;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			temp = A[i][j];
			B[j][i] = temp;
		}
	}

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
	/* Register your solution function */
	registerTransFunction(transpose_submit, transpose_submit_desc);

	/* Register any additional transpose functions */
	registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; ++j) {
			if (A[i][j] != B[j][i]) {
				return 0;
			}
		}
	}
	return 1;
}

