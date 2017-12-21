// IP_book.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "My_funs.h"
#include "IPbook.h"
#include "chp09.h"
#include "chp10.h"
#include "SegWord.h"

using namespace std;
using namespace cv;

#define IMG_PATH  "..//figures//lotus.jpg"
#define T_PATH  "..//figures//lotus_t1.jpg"


void rotate_keep_size(const Mat& img, Mat& dst, double degree, double scale){

	if (img.empty())
		cerr<<"can not load image"<<endl;

	// 定义仿射变换的，中心，角度，尺度
	Point2f center = Point2f(img.cols/2.0, img.rows/2.0);

	// 获取变换矩阵
	Mat rot = getRotationMatrix2D(center,degree,scale);

	// 获取变换之后的 区域，这个很重要，不然的话，变换之后的图像显示不全
	Rect bbox;
	bbox = RotatedRect(center,Size(scale*img.cols,scale*img.rows),degree).boundingRect();

	// 对变换矩阵的最后一列做修改，重新定义变换的 中心

	rot.at<double>(0,2) += bbox.width/2 - center.x;
	rot.at<double>(1,2) += bbox.height/2 - center.y;

	warpAffine(img,dst,rot, bbox.size());

}


void Template_match_1(void){
	Mat img = imread(IMG_PATH);
	Mat t1 = imread(T_PATH);

	if (img.empty() || t1.empty())
		cerr<<"can not read image"<<endl;

	imshow("img",img);
	imshow("template",t1);

	// 匹配
	Mat dst;
	matchTemplate(img,t1,dst,CV_TM_CCOEFF_NORMED);

	// 找到最佳匹配位置
	double minv, maxv;
	Point minLoc,maxLoc;
	minMaxLoc(dst,&minv,&maxv,&minLoc,&maxLoc);

	rectangle(img,Rect(maxLoc,Size(t1.cols,t1.rows)),Scalar(0,0,255));
	imshow("result",img);

	// 对模板进行仿射变换
	Mat rt1;
	rotate_keep_size(t1,rt1,60,1);
	imshow("rt1",rt1);
	matchTemplate(img,rt1,dst,CV_TM_CCOEFF_NORMED);

	// 找到最佳匹配位置
	minMaxLoc(dst,&minv,&maxv,&minLoc,&maxLoc);

	rectangle(img,Rect(maxLoc,Size(rt1.cols,rt1.rows)),Scalar(255,0,0));
	imshow("result",img);


}
