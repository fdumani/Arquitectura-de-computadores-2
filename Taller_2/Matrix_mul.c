#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define size 500
     
int main()
{
  int m = size;
  int n = size;
  int p = size;
  int q = size;
  int c, d, k, sum = 0;
  int first[size][size], second[size][size], multiply[size][size];
  double start_time, run_time;
 

 
  for (c = 0; c < m; c++){
    for (d = 0; d < n; d++){
      first[c][d] = rand() % 255;
    }
  }
 
  if (n != p)
    printf("The matrices can't be multiplied with each other.\n");
  else
  {
    int temp = omp_get_num_procs();
    printf("%d\n", temp);

 
    for (c = 0; c < p; c++){
      for (d = 0; d < q; d++){
        second[c][d] = rand() % 255;
      }
    }
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
      
      for (c = 0; c < m; c++) {
        #pragma omp for reduction(+:sum)
        for (d = 0; d < q; d++) {
          for (k = 0; k < p; k++) {
            sum = sum + first[c][k]*second[k][d];
          }
   
          multiply[c][d] = sum;
          sum = 0;
        }
      }
    }
    run_time = omp_get_wtime() - start_time;
    printf("Calculated matrix multiplication of %d * %d in %f seconds \n",size,size,run_time);
 

/*
    printf("Product of the matrices:\n");
 
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++)
        printf("%d\t", multiply[c][d]);
 
      printf("\n");
    }
*/
  }

  return 0;
}