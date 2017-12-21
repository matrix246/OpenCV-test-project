// csdn_code.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



//#define IMG_PATH  "..//figures//12.jpg"

#define IMG_PATH  "..//figures//lotus.jpg"

int main()
{

	Mat img = imread(IMG_PATH);
	if (img.empty())
		cerr<<"can not load image"<<endl;


	Mat roi = img(Rect(270,160,img.cols/4,img.rows/4));
	imshow("roi",roi);
	imwrite("roi.jpg",roi);

	waitKey();
	system("pause");
	return 0;
}
