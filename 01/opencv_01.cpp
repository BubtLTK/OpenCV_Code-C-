#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(){
	string src = "./sky.jpg";
	string src1 = "./addimg.png";
	Mat img = imread(src);
	Mat img1 = imread(src1);
	if(img.empty()||img1.empty()){
		cout<<"can not load images"<<endl;
		return -1;
	}
	int h = img.rows/4;
       	int w = img.cols/4;	
	resize(img,img,Size(w,h));
	resize(img1,img1,Size(w,h));
	imshow("img1",img);
	imshow("img2",img1);
	Mat dst;
	dst.create(img.size(),img.type());
//	dst = 0.6*img + 0.4*img1;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			dst.at<Vec3b>(i,j)[0] = 0.6*img.at<Vec3b>(i,j)[0]+0.4*img1.at<Vec3b>(i,j)[0];
			dst.at<Vec3b>(i,j)[1] = 0.6*img.at<Vec3b>(i,j)[1]+0.4*img1.at<Vec3b>(i,j)[1];
			dst.at<Vec3b>(i,j)[2] = 0.6*img.at<Vec3b>(i,j)[2]+0.4*img1.at<Vec3b>(i,j)[2];
		}
	}
	imshow("img3",dst);
	//实现改变图像对比度与亮度
	Mat zero(img.size(),CV_8UC3,Scalar(0,0,0));//构造全黑图像
	addWeighted(img,0.6,zero,0.4,25,dst);
	imshow("img4",dst);
	waitKey(0);
	imwrite("new_img.jpg",dst);
	return 0;
}
