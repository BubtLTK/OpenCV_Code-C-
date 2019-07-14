#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
	Mat img = imread("fuhua.jpg");
	Mat imgd = imread("fuhua.jpg");
	if(img.empty()||imgd.empty()){
		cout<<"no file"<<endl;
		return 0;
	}
	Mat hsvs,hsvd;
	cvtColor(img,hsvs,CV_BGR2HSV);
	cvtColor(imgd,hsvd,CV_BGR2HSV);
	int channels[]={0};
	const int nHistSize[] = {20};
	float rangeh[] = {0,180};
	const float *range[] = {rangeh};
	Mat hist;
	//针对h通道（色相），生成直方图
	calcHist(&imgd,1,channels,Mat(),hist,1,nHistSize,range,true,false);
	//归一化
	normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());
	Mat backProject;
	//直方图反向投影
	calcBackProject(&hsvd,1,channels,hist,backProject,range,1,true);
	imshow("src",img);
	imshow("backProject",backProject);
	waitKey(0);
	return 0;
}
