#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(){
	VideoCapture cap;
	/*
	cap.open("video.mp4");//读取网络视频
	if(!cap.isOpened()){
		cout<<"error"<<endl;
		return -1;
	}
	int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	int frameRate = cap.get(CV_CAP_PROP_FPS);
	int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	cout<<"视频宽度"<<width<<endl;
	cout<<"视频高度"<<height<<endl;
	cout<<"帧率"<<frameRate<<endl;
	cout<<"视频总帧数"<<totalFrames<<endl;
	Mat frame;
	while(1){
		cap.read(frame);//等价于cap>>frame
		if(frame.empty())//空帧退出循环
			break;
		imshow("video",frame);
		waitKey(20);
	}
	cap.release();//释放资源
	*/
	cap.open(0);//打开摄像头
	if(!cap.isOpened()){
		cout<<"error"<<endl;
		return -1;
	}
	Mat frame;
	while(1){
		cap>>frame;
		flip(frame,frame,1);//图像左右翻转
		imshow("captrue",frame);
		int c = waitKey(20);
		if(c==27)
			break;
	}
	return 0;
}
