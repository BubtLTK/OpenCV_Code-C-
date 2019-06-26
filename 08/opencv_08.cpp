#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void histMatch(Mat ,Mat ,Mat &);
int main(){
	Mat imgsrc = imread("fuhua.jpg");
	if(imgsrc.empty()){
		cout<<"error"<<endl;
		return -1;
	}
	//HSV颜色空间下的直方图（二维）
	Mat img;
	cvtColor(imgsrc,img,CV_BGR2HSV);
	imshow("img",img);
	int hbins = 30;
	int sbins = 32;
	int channels[] = {0,1};
	int histSize[] = {hbins,sbins};
	float hrange[] = {0,180};
	float srange[] = {0,256};
	const float *range[] = {hrange,srange};
	Mat hist;
	calcHist(&img,1,channels,Mat(),hist,2,histSize,range,true,false);
	double maxval;
	minMaxLoc(hist,0,&maxval,0,0);//获取hist中的最大值
	int bw = 10;
	Mat histimg = Mat::zeros(Size(bw*sbins,bw*hbins),CV_8UC1);
	for(int i=0;i<hbins;i++){
		for(int j=0;j<sbins;j++){
			float pval = hist.at<float>(i,j);
			int newval = cvRound(pval*255/maxval);
			rectangle(histimg,Point(j*bw,i*bw),Point((j+1)*bw-1,(i+1)*bw-1),newval,CV_FILLED);
		}
	}
	imshow("hist",histimg);
	//直方图匹配
	Mat imgdst = imread("dst.jpg");
	if(imgdst.empty()||imgdst.channels()!=3){
		cout<<"error"<<endl;
		return -1;
	}
	Mat srcBGR[3];
	Mat dstBGR[3];
	Mat newBGR[3];
	split(imgsrc,srcBGR);
	split(imgdst,dstBGR);
	histMatch(srcBGR[0],dstBGR[0],newBGR[0]);
	histMatch(srcBGR[1],dstBGR[1],newBGR[1]);
	histMatch(srcBGR[2],dstBGR[2],newBGR[2]);
	Mat newimg;
	merge(newBGR,3,newimg);
	imshow("imgsrc",imgsrc);
	imshow("imgdst",imgdst);
	imshow("newimg",newimg);
	waitKey(0);
	return 0;
}

void histMatch(Mat src,Mat dst,Mat &newimg){
	int channels[] = {0};
	int histSize[] = {256};
	float range[] = {0,255};
	const float *hrange[] = {range};
	Mat histsrc;
	Mat histdst;
	calcHist(&src,1,channels,Mat(),histsrc,1,histSize,hrange,true,false);
	calcHist(&dst,1,channels,Mat(),histdst,1,histSize,hrange,true,false);
	double psrc[256] = {0.0};//存储源图像的各灰度级的概率
	double pdst[256] = {0.0};//存储目标图像的各灰度级的概率
	int sumps = src.rows*src.cols;
	int sumpd = dst.rows*src.cols;
	for(int i=0;i<256;i++){
		psrc[i] = (double)(histsrc.at<float>(i)/sumps);
		pdst[i] = (double)(histdst.at<float>(i)/sumpd);
	}
	//计算源图像与目标图像分别与均衡化后的图像的像素值映射关系
	int src2equal[256] = {0};
	int dst2equal[256] = {0};
	for(int i=0;i<256;i++){
		double st = 0.0;
		double dt = 0.0;
		for(int j=0;j<=i;j++){
			st += psrc[j];
			dt += pdst[j];
		}
		src2equal[i] = cvRound(255*st);
		dst2equal[i] = cvRound(255*dt);
	}
	//计算源图像像素与目标图像像素的映射关系
	int pmatch[256] = {0};
	for(int i=0;i<256;i++){
		int value = src2equal[i];//源图像像素值到均衡化后的图像像素值的映射
		int k = 0;
		int v = 0;
		int vnoe = 0;//存储最接近的灰度值（源图像像素均衡化后的像素值与目标图像像素均衡化后的像素值的比较）
		int flag = 256;
		for(int j=0;j<256;j++){
			if(value == dst2equal[j]){
				k++;
				v += j;
			}
			if(value < dst2equal[j]&&(dst2equal[i]-value)<flag){
				vnoe = j;
				flag = dst2equal[j]-value;
			}
		}
		if(k == 0){
			pmatch[i] = vnoe;//接近值（映射一对无的情况）
		}
		else{
			pmatch[i] = v/k;//平均值（映射一对多的情况）
		}
	}
	//生成新图像
	newimg = Mat::zeros(Size(src.cols,src.rows),CV_8UC1);
	for(int i=0;i<src.rows;i++){
		for(int j=0;j<src.cols;j++){
			newimg.at<uchar>(i,j) = pmatch[src.at<uchar>(i,j)];
		}
	}
}
