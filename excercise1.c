// 
//
// gcc excercise1.c -o excercise1 -D TILE_MODE -D N=10000 -D k=100
//
// perf stat -o perf.txt ./helloworld; cat perf.txt | grep "seconds time elapsed" | sed  "s/ *//" | sed "s/ seconds.*//" >> time_results.txt
//
// for i in {1..10}; do echo $i; done;
//
//

#ifndef N
		
	#define DEBUG_PRINT   // automatically turn on debug printing
	
	#define N 10000  	  // default array size 10,000 ~ 1.5 seconds on my computer --> 12,000 complains on my computer
	#define k 100	 	  // default tile size
	
#endif

#ifdef DEBUG_PRINT
#include<stdio.h>
#include <sys/time.h>
#endif

// globally defined arrays
double A[N][N];
double B[N][N];

#ifdef DEBUG_PRINT
struct timeval start,end;
#endif

int main() {
	
	#ifdef DEBUG_PRINT
	printf("DEBUG PRINT: ON\n", N);
	
	#ifdef TILE_MODE
	printf("TILE MODE: ON\n", N);
	#else
	printf("TILE MODE: OFF\n", N);
	#endif
	
	printf("Defaults:\n", N);
	printf("N = %lu\n", N);
	printf("k = %lu\n\n", k);
	
	gettimeofday(&start, NULL);
	#endif
	
	// -----------  program ------------ //
	
	int i, j, m, n, t;
	
	#ifdef TILE_MODE
	
	// block version
	t = (N%k == 0)? N/k : N/k + 1;  // number of iterations
	for(m = 0; m < t; m++) {
		for(n = 0; n < t; n++) {
	
			for(i = m*k; i < (m*k+k) && i<N; i++) {
				for(j = n*k; j < (n*k+k) && j<N; j++) {
					A[i][j] += B[j][i];
				}
			}
			
		}		
	}
	
	#else
	
	// regular version
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {			
			A[i][j] += B[j][i];
		}
	}
	
	#endif
	
	// -------------------------------- //
	
	#ifdef DEBUG_PRINT
	gettimeofday(&end,NULL);
	printf("Seconds elapsed: %f\n", (end.tv_sec*1000000.0 + end.tv_usec - start.tv_sec*1000000.0 - start.tv_usec) / 1000000.0);
	#endif
	
}
