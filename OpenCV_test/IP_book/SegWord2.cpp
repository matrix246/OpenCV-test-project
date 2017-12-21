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

#define IMG_PATH  "..//figures//111.jpg"

void step_1_erode(Mat& img){

	cvtColor(img,img,CV_BGR2GRAY,1);
	threshold(img,img,90,255,THRESH_OTSU);
	img = 255 - img;
	imshow("after otsu",img);

	Mat ker = Mat::ones(3,7,CV_8U);
	//Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(3,3));
	dilate(img,img,ker,Point(0,1));
	imshow("after dilate",img);

}


void step_2_find_conection(const Mat& original_img, Mat& img_erode){

	// find contours of img
	vector<vector<Point>> contours;
	findContours(img_erode,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

	Scalar color = Scalar(0,0,255);
	// 在原图上画出边界
	Mat img1 = original_img.clone();
	drawContours(img1,contours,-1,color);
	imshow("img with contours",img1);

	// 在原图上画出，包括边界的最大矩形
	Mat img2 = original_img.clone();
	Rect ri;
	vector<vector<Point>>::iterator itcon;
	for (itcon = contours.begin(); itcon != contours.end(); itcon++)
	{
		ri = boundingRect(*itcon);
		if (ri.height >10 && (ri.width * 1.0 / ri.height) > 0.2)
			rectangle(img2,ri,color);
	}
	imshow("img with rectangle",img2);


	// 如果有旋转的话，需要使用下面的方法画出旋转的方框
	Mat img3 = original_img.clone();
	vector<RotatedRect> minRect(contours.size());
	for (int i = 0; i < contours.size(); i++){
		minRect[i] = minAreaRect(Mat(contours[i]));
		Point2f rect_points[4];
		minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(img3,rect_points[j],rect_points[(j+1)%4],color,1,8);
	}
	imshow("img with rotated rectangle",img3);

}

void Seg_word_2(){
	Mat img = imread(IMG_PATH);
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);
	Mat img_erode = img.clone();

	step_1_erode(img_erode);

	step_2_find_conection(img,img_erode);

}
