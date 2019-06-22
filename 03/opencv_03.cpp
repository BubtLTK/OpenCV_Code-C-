#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Mat showChannelsinBGR(vector<Mat> channels,int num){
	vector<Mat> newchannels;
	Mat zero = Mat::zeros(channels[0].rows,channels[0].cols,channels[0].type());
	for(int i=0;i<3;i++){
		if(i==num)
			newchannels.push_back(channels[i]);
		else
			newchannels.push_back(zero);
	}
	Mat newimg;
	//通道合并，newimg为输出
	merge(newchannels,newimg);
	return newimg;
}

int main(){
	Mat img = imread("RGB.jpg");
	int h = img.rows;
	int w = img.cols;
	resize(img,img,Size(w/2,h/2));
	vector<Mat> channels;
	split(img,channels);
	imshow("RGB",img);
	//转灰度图
	Mat gray;
	cvtColor(img,gray,cv::COLOR_BGR2GRAY);
	imshow("Gray",gray);
	//灰度空间（单通道）显示通道
	imshow("Blue",channels[0]);
	imshow("Green",channels[1]);
	imshow("Red",channels[2]);
	//BGR颜色空间（三通道）显示通道
	imshow("Blue in BGR",showChannelsinBGR(channels,0));
	imshow("Green in BGR",showChannelsinBGR(channels,1));
	imshow("Red in BGR",showChannelsinBGR(channels,2));
	waitKey(0);
	return 0;
}
