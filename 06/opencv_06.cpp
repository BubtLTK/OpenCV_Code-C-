#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
	Mat img = imread("queban.jpg");
	if(img.empty()){
		cout<<"error"<<endl;
		return -1;
	}
	imshow("img",img);
	Size size(5,5);
	Mat gaussimg;
	//高斯模糊
	GaussianBlur(img,gaussimg,size,0,0);//sigmaX=sigmaY=0时，sigmaX和sigmaY由ksize自动确定
	imshow("GaussionBlur",gaussimg);
	//高斯双边滤波
	Mat blfilter;
	bilateralFilter(img,blfilter,0,100.5,15.5);
	imshow("bilateralBlur",blfilter);
	//均值迁移
	Mat meanshiftimg;
	pyrMeanShiftFiltering(img,meanshiftimg,10,50);
	imshow("MeanShift",meanshiftimg);

	waitKey(0);
	return 0;
}
