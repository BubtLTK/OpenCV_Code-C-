#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
	Mat img = imread("fuhua.jpg");
	int h = img.rows;
	int w = img.cols;
	resize(img,img,Size(w/2,h/2));
	Mat imgf = img.clone();
	imshow("img",img);
	Rect rect(300,30,70,70);
	//提取ROI
	Mat roi_face(img,rect);//roi_face与img公用一组数据，roi_face = Scalar(0,255,0)操作也会修改img的数据
	imshow("face",roi_face);
	//改变ROI内的图像内容
	cvtColor(roi_face,roi_face,COLOR_BGR2GRAY);
	cvtColor(roi_face,roi_face,COLOR_GRAY2BGR);
	roi_face.copyTo(img(rect));
	imshow("newimg",img);
	//泛洪填充
	Mat mask = Mat::ones(Size(w/2+2,h/2+2),CV_8UC1);
	mask(Rect(301,31,70,70)) = Scalar(0);
	Rect ccomp;
	floodFill(imgf,mask,Point(326,40),Scalar(0,0,255),&ccomp,Scalar(20,20,20),Scalar(20,20,20));
	imshow("img_floodFill",imgf);
	waitKey(0);
	return 0;
}
