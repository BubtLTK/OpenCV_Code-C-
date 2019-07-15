#include<opencv2/opencv.hpp>
using namespace cv;
__global__ void bitwise_image_kernel(cuda::PtrStepSz<uchar3> ,cuda::PtrStepSz<uchar3> );
void bitwise_image(cuda::GpuMat ,cuda::GpuMat );
