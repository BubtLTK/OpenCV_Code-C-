#include<iostream>
#include<opencv2/opencv.hpp>
#include<time.h>
#include<stdlib.h>
using namespace std;
using namespace cv;
//加噪声
Mat AddNoise(Mat img,int num){
	Mat newimg = img.clone();
	time_t t;
	int h = img.rows;
	int w = img.cols;
	srand((unsigned int)time(&t));
	for(int i=0;i<num;i++){
		int rand_h = rand()%h;
		int rand_w = rand()%w;
		int newvalue1 = rand()%256;
		int newvalue2 = rand()%256;
		int newvalue3 = rand()%256;
		newimg.at<Vec3b>(rand_h,rand_w)[0] = newvalue1;
		newimg.at<Vec3b>(rand_h,rand_w)[1] = newvalue2;
		newimg.at<Vec3b>(rand_h,rand_w)[2] = newvalue3;
	}
	return newimg;
}
//均值模糊
Mat AverBlur(Mat img){
	Mat dst;
	blur(img,dst,Size(5,5));
	return dst;
}
//中值模糊
Mat MedianBlur(Mat img){
	Mat dst;
	medianBlur(img,dst,5);
	return dst;
}
//自定义模糊
Mat DIYBlur(Mat img,Mat kernel){
	Mat diyimg;
	filter2D(img,diyimg,img.depth(),kernel);
	return diyimg;
}

int main(){
	Mat img = imread("fuhua.jpg");
	if(img.empty()){
		cout<<"error"<<endl;
		return -1;
	}
	int h = img.rows;
	int w = img.cols;
	resize(img,img,Size(w/2,h/2));

	Mat img_noise = AddNoise(img,10000);
	cout<<"img:"<<endl;
	cout<<"rows:"<<img.rows<<" cols:"<<img.cols<<" channels:"<<img.channels()<<endl;
	imshow("img",img);

	cout<<"img_noise:"<<endl;
	cout<<"rows:"<<img_noise.rows<<" cols:"<<img_noise.cols<<" channels:"<<img_noise.channels()<<endl;
	imshow("noise_img",img_noise);

	Mat averblur = AverBlur(img_noise);
	cout<<"AverBlur:"<<endl;
	cout<<"rows:"<<averblur.rows<<" cols:"<<averblur.cols<<" channels:"<<averblur.channels()<<endl;
	imshow("AverBlur",averblur);

	Mat medianblur = MedianBlur(img_noise);
	cout<<"MedianBlur:"<<endl;
	cout<<"rows:"<<medianblur.rows<<" cols:"<<medianblur.cols<<" channels:"<<medianblur.channels()<<endl;
	imshow("MedianBlur",medianblur);

	Mat mask = (Mat_<char>(3,3)<<0,-1,0,-1,4,-1,0,-1,0);//提取边缘，矩阵元素和为0
	//Mat mask = (Mat_<char>(3,3)<<0,-1,0,-1,5,-1,0,-1,0);//锐化，矩阵元素和为1
	Mat diyblur = DIYBlur(img,mask);
	cout<<"DIYBlur:"<<endl;
	cout<<"rows:"<<diyblur.rows<<" cols:"<<diyblur.cols<<" channels:"<<diyblur.channels()<<endl;
	imshow("DIYBlur",diyblur);

	waitKey(0);
	return 0;
}
