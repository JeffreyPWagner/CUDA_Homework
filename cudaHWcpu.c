// cudaHWcpu.c
//
// Program to generate and get the dot product of two vectors using a CPU

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ARRAY_SIZE 1000000000

int main (int argc, char *argv[])
{
   struct timeval start, end;

   int *result = (int *) malloc(ARRAY_SIZE * sizeof(int));

   gettimeofday(&start, NULL);  

   int *force = (int *) malloc(ARRAY_SIZE * sizeof(int));
   int *distance = (int *) malloc(ARRAY_SIZE * sizeof(int));

   long k = ARRAY_SIZE / 2;

   for (long x=0; x < ARRAY_SIZE; x++) {
        if (x < k) {
            force[x] = x + 1;
        } else if (x > k) {
            force[x] = x - ((x - k) * 2);
        } else {
            force[x] = x;
        }
        distance[x] = x % 10 + 1;
        result[x] = force[x] * distance[x];
   }

   gettimeofday(&end, NULL);

   long seconds = (end.tv_sec - start.tv_sec);
   long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

   printf("Processing time elpased is %zu seconds or %zu micros\n", seconds, micros);

   long i;
   long sum = 0;
 
   printf ("Summing final result\n");
   for (i=0; i < ARRAY_SIZE; i++)
      sum += result[i];

   printf ("%zu ", sum);
   printf ("\n");
   
   free (result);
   
   return 0;
}
