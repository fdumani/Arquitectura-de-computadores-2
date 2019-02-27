///////////////////////////////////////////////////////////////////////
// Fabrizio Dumani Bernardi
// Carné: 2015182277
// Arquitectura de computadores II
// Taller 2: OpenMP
// Algoritmo SAXPY secuencial
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define array_size 1000000 // Size for arrays to be used
#define a 10 // Constant for SAXPY algorithm

int main ()
{
	double start_time, run_time;
	int x[array_size];
	int y[array_size];
	
	int i;
	// The next loop fills arrays "x" and "y" with random values
	for (i=0; i < array_size; i++) {
		x[i] = rand() % 255; //Create a random number between 0 and 255
		y[i] = rand() % 255;
	}
	
	int j;
	//The next loop executes SAXPY algorithm between "x" and "y" using "a" as the constant for multiplication
	start_time = omp_get_wtime();
	for (j=0; j < array_size; j++) {
		
		//printf("%d + 10*%d = ", y[j], x[j]);
		y[j] = a*x[j] + y[j]; // SAXPY function
		//printf("%d\n", y[j]);
		
	}
	run_time = omp_get_wtime() - start_time;
	printf("Run time = %f\n", run_time);
}
