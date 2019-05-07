///////////////////////////////////////////////////////////////////////
// Fabrizio Dumani Bernardi
// Carné: 2015182277
// Arquitectura de computadores II
// Taller 4: OpenMP, parte II
// Algoritmo SAXPY paralelo con vectores de 4
///////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<arm_neon.h>

#define array_size 1000000 // Size for arrays to be used
#define a 10 // Constant for SAXPY algorithm

int main ()
{
	double start_time, run_time;
	int16_t c[4]; // Vector for constant multiplication
	// Vectors for saxpy operation
	int16_t x[array_size];
	int16_t y[array_size];
	// Pointers for NEOS vector
	int16_t *xp = x;
	int16_t *yp = y;
	int16_t *cp = c;
	
	int i;
	// The next loop fills arrays "x" and "y" with random values
	for (i=0; i < array_size; i++) {
		x[i] = rand() % 255; //Create a random number between 0 and 255
		y[i] = rand() % 255;
	}

	// Fill constant vector with a value in this case 2
	c[0] = 2;
	c[1] = 2;
	c[2] = 2;
	c[3] = 2;
	int16x4_t vecc;
	// Load constants into a vector
	vecc = vld1_s16(cp);

	int j;
	//The next loop executes SAXPY algorithm between "x" and "y" using "a" as the constant for multiplication
	start_time = omp_get_wtime();
	#pragma omp parallel 
	{
		#pragma omp for
		for (j=0; j < array_size; j+=4) {
			int16x4_t vec1;
			int16x4_t vec2;

			// Extract two vectors for x and y array at pointer positions
			vec1 = vld1_u16(xp);
			vec2 = vld1_u16(yp);
			
			// Multiply x vector with constant vector
			vec1 = vmul_s16(vec1, vecc);
			// Add previous result to y vector
			vec2 = vadd_s16(vec1, vec2);
			// Store result in original y array
			vst1_u16(yp, vec2);

			// Move pointers
			yp += 4;
			xp += 4;
			
		}
	}
	run_time = omp_get_wtime() - start_time;
	printf("Run time = %f\n", run_time);
}