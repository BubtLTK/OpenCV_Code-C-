#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
/*函数原型
CV_EXPORTS void calcHist( const Mat* images,
                          int nimages,
                          const int* channels,
                          InputArray mask,
                          OutputArray hist,
                          int dims,
                          const int* histSize,
                          const float** ranges,
                          bool uniform = true,
                          bool accumulate = false );
 */
int main(){
	Mat img = imread("hanbing.jpg");
	if(img.empty()){
		cout<<"error"<<endl;
		return -1;
	}
	int h = img.rows;
	int w = img.cols;
	resize(img,img,Size(w/2,h/2));
	imshow("img",img);
	//直方图（灰度）
	int channels[3] = {0,1,2};
	const int nHistSize[] = {256};
	float range[] = {0,255};
	const float *ranges[] = {range};
	Mat histB,histG,histR;
	calcHist(&img,1,&channels[0],Mat(),histB,1,nHistSize,ranges,true,false);
	calcHist(&img,1,&channels[1],Mat(),histG,1,nHistSize,ranges,true,false);
	calcHist(&img,1,&channels[2],Mat(),histR,1,nHistSize,ranges,true,false);
	int HW = 800;
	int HH = 600;
	int BW = cvRound((double)HW/nHistSize[0]);//cvRound()：返回跟参数最接近的整数值，即四舍五入；
	Mat histimg(Size(HW,HH),CV_8UC3,Scalar(255,255,255));
	normalize(histB,histB,0,HH,NORM_MINMAX,-1,Mat());//归一化
	normalize(histG,histG,0,HH,NORM_MINMAX,-1,Mat());
	normalize(histR,histR,0,HH,NORM_MINMAX,-1,Mat());
	for(int i=0;i<nHistSize[0]-1;i++){//开始绘制
		line(histimg,Point(i*BW,HH-cvRound(histB.at<float>(i))),Point((i+1)*BW,HH-cvRound(histB.at<float>(i+1))),Scalar(255,0,0),2,8,0);
		line(histimg,Point(i*BW,HH-cvRound(histG.at<float>(i))),Point((i+1)*BW,HH-cvRound(histG.at<float>(i+1))),Scalar(0,255,0),2,8,0);
		line(histimg,Point(i*BW,HH-cvRound(histR.at<float>(i))),Point((i+1)*BW,HH-cvRound(histR.at<float>(i+1))),Scalar(0,0,255),2,8,0);
	}
	imshow("hist_img",histimg);
	//直方图均衡化（彩色图）
	vector<Mat> imgC;
	split(img,imgC);
	imshow("B",imgC[0]);
	imshow("G",imgC[1]);
	imshow("R",imgC[2]);
	for(int i=0;i<3;i++){
		equalizeHist(imgC[i],imgC[i]);
	}
	imshow("B_E",imgC[0]);//均衡化后的Blue通道
	imshow("G_E",imgC[1]);
	imshow("R_E",imgC[2]);
	Mat equalizeimg;
	merge(imgC,equalizeimg);
	imshow("equalize",equalizeimg);
	//直方图（均衡化后）
	Mat histBe,histGe,histRe;
	calcHist(&equalizeimg,1,&channels[0],Mat(),histBe,1,nHistSize,ranges,true,false);
	calcHist(&equalizeimg,1,&channels[1],Mat(),histGe,1,nHistSize,ranges,true,false);
	calcHist(&equalizeimg,1,&channels[2],Mat(),histRe,1,nHistSize,ranges,true,false);
	Mat histimge(Size(HW,HH),CV_8UC3,Scalar(255,255,255));
	normalize(histBe,histBe,0,HH,NORM_MINMAX,-1,Mat());
	normalize(histGe,histGe,0,HH,NORM_MINMAX,-1,Mat());
	normalize(histRe,histRe,0,HH,NORM_MINMAX,-1,Mat());
	for(int i=0;i<nHistSize[0]-1;i++){
		line(histimge,Point(i*BW,HH-cvRound(histBe.at<float>(i))),Point((i+1)*BW,HH-cvRound(histBe.at<float>(i+1))),Scalar(255,0,0),2,8,0);
		line(histimge,Point(i*BW,HH-cvRound(histGe.at<float>(i))),Point((i+1)*BW,HH-cvRound(histGe.at<float>(i+1))),Scalar(0,255,0),2,8,0);
		line(histimge,Point(i*BW,HH-cvRound(histRe.at<float>(i))),Point((i+1)*BW,HH-cvRound(histRe.at<float>(i+1))),Scalar(0,0,255),2,8,0);
	}
	imshow("hist_img_equalize",histimge);
	waitKey(0);
	return 0;
}
