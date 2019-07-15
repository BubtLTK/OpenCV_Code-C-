#include<iostream>
#include<stdio.h>
#include<opencv2/opencv.hpp>
#include"opencvgpu.h"
using namespace std;
using namespace cv;
int main(){
	Mat h_src,h_dst;
	cuda::GpuMat d_src,d_dst;
	h_src = imread("fuhua.jpg");
	if(h_src.empty()){
		cout<<"ERROR"<<endl;
		return -1;
	}
	d_src.upload(h_src);
	d_dst = cuda::GpuMat(h_src.rows,h_src.cols,CV_8UC3,Scalar(0,0,0));
	h_dst = Mat(h_src.rows,h_src.cols,CV_8UC3,Scalar(0,0,0));
	bitwise_image(d_src,d_dst);
	d_dst.download(h_dst);
	imshow("src",h_src);
	imshow("dst",h_dst);
	waitKey(0);
	return 0;
}


