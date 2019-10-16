// cudaHW.cu
//
// driver and kernel call

#include <stdio.h>

#define THREADS_PER_BLOCK 256
 
__global__ void vDotProd_d (int *force, int *distance, int *result, int n)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int i = n / 2;
    if (x < n) {
        if (x < i) {
            force[x] = x + 1;
        } else if (x > i) {
            force[x] = x - ((x - i) * 2);
        } else {
            force[x] = x;
        }
        distance[x] = x % 10 + 1;
        result[x] = force[x] * distance[x];
    }	
}

extern "C" void gpuDotProd (int *result_h, int arraySize)
{
    int *force;
    int *distance;
    int *result;

	cudaMalloc ((void**) &force, sizeof(int) * arraySize);
	cudaMalloc ((void**) &distance, sizeof(int) * arraySize);
	cudaMalloc ((void**) &result, sizeof(int) * arraySize);
	
	vDotProd_d <<< ceil((float) arraySize/THREADS_PER_BLOCK), THREADS_PER_BLOCK >>> (force, distance, result, arraySize);
	
	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
		printf ("CUDA error: %s\n", cudaGetErrorString(err));
		
	cudaMemcpy (result_h, result, sizeof(int) * arraySize, cudaMemcpyDeviceToHost);
	cudaFree (force);
	cudaFree (distance);
	cudaFree (result);
}
