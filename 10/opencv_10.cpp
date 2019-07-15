#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
	Mat src = imread("34.jpg");
	Mat example = imread("example.jpg");
	if(src.empty()||example.empty()){
		cout<<"加载错误"<<endl;
		return -1;
	}
	Mat dst(src.rows-example.rows+1,src.cols-example.cols+1,CV_32FC1);
	int x;
	cout<<"输入匹配模式：";
	cin>>x;
	matchTemplate(src,example,dst,x);
	double minVal,maxVal;
	Point minLoc,maxLoc;
	Point matchLoc;
	minMaxLoc(dst,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
	if(x==1){
		matchLoc = minLoc;
	}
	else if(x==3||x==5){
		matchLoc = maxLoc;
	}
	Mat mask = src.clone();
	rectangle(mask,matchLoc,Point(matchLoc.x+example.cols,matchLoc.y+example.rows),Scalar(0,0,255),4,8,0);
	imshow("location",mask);
	waitKey(0);
	return 0;
}
