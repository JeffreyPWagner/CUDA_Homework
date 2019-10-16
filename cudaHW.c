// cuaHW.c
//
// Program to generate and get the dot product of two vectors using a GPU

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ARRAY_SIZE 1000000000

extern void gpuDotProd(int *result, int size);

int main (int argc, char *argv[])
{
   struct timeval start, end;

   int *result = (int *) malloc(ARRAY_SIZE * sizeof(int));

   gettimeofday(&start, NULL);  

   gpuDotProd (result, ARRAY_SIZE);

   gettimeofday(&end, NULL);

   long seconds = (end.tv_sec - start.tv_sec);
   long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

   printf("Parallel time elpased is %zu seconds or %zu micros\n", seconds, micros);

   int i;
   long sum = 0;
 
   printf ("Summing final result\n");
   for (i=0; i < ARRAY_SIZE; i++)
      sum += result[i];

   printf ("%zu ", sum);
   printf ("\n");
   
   free (result);
   
   return 0;
}
