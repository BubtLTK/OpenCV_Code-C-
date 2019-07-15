#include<stdio.h>
#include<stdlib.h>
#include"opencvgpu.h"
__global__ void bitwise_image_kernel(cuda::PtrStepSz<uchar3> d_src,cuda::PtrStepSz<uchar3> d_dst){
	unsigned int x = blockDim.x*blockIdx.x+threadIdx.x;
	unsigned int y = blockDim.y*blockIdx.y+threadIdx.y;
	if (x<d_src.cols&&y<d_src.rows){
		d_dst(y,x).x = 255-d_src(y,x).x;
		d_dst(y,x).y = 255-d_src(y,x).y;
		d_dst(y,x).z = 255-d_src(y,x).z;
	}
}

void bitwise_image(cuda::GpuMat src,cuda::GpuMat dst){
	int uint = 32;
	dim3 thread(uint,uint);
	dim3 block((src.cols+uint-1)/uint,(src.rows+uint-1)/uint);
	bitwise_image_kernel<<<block,thread>>>(src,dst);
}
