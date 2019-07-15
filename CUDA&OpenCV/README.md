# CUDA与OpenCV的结合编程    
> 前提：安装好CUDA以及支持CUDA的OpenCV    
> 编译命令（以opencv1文件夹下的代码为例）：   
> > nvcc -c opencvgpu.o opencvgpu.cu `pkg-config --libs --cflags opencv` -ldl   
> > ar crv libopencvgpu.a opencvgpu.o    
> > nvcc -o opencv1 opencv1.cu libopencvgpu.a `pkg-config --libs --cflags opencv` -ldl    
## opencv1 实现图像反相    
