#include<stdio.h>

// default N=10
#ifndef N
	#define TEST_MODE

	#define N 15  // array size
	#define k 4	 // tile size
#endif

// globally defined arrays
double A[N][N];
double B[N][N];

double C[N][N];  // test
double D[N][N];  // actual

// prototype
void printArray(double array[N][N]);

int main() {

	#ifdef TEST_MODE
	{
		// init array with values
		int i;
		int j;
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				A[i][j] = i*N+j+1;
				B[i][j] = i+j+1;
			}
		}
	}
	#endif
	
	printArray(A);
	printf("\n");
	
	printArray(B);
	printf("\n");
	printf("\n");
	
	int i, j, m, n, t;
	
	// block version
	t = (N%k == 0)? N/k : N/k + 1;  // number of iterations
	for(m = 0; m < t; m++) {
		for(n = 0; n < t; n++) {
	
			for(i = m*k; i < (m*k+k) && i<N; i++) {
				for(j = n*k; j < (n*k+k) && j<N; j++) {
					
					C[i][j] = A[i][j] + B[j][i];
					
				}
			}
			
		}		
	}
	
	printf("\n\n");
	
	// regular version
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			
			D[i][j] = A[i][j] + B[j][i];
			
		}
	}
	
	printArray(C);
	printf("\n");
	
	printArray(D);
	printf("\n");
	
}

void printArray(double array[N][N]) {

	int i;
	int j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%.0lf\t", array[i][j]);
		}
		printf("\n");
	}
	
}
