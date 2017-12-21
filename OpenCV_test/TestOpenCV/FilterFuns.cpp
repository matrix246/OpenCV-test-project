// MyProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


using namespace std;
using namespace cv;

void DifferentFilters(const Mat& img) {


	// use gaussian filter
	Mat GaussImg;
	GaussianBlur(img, GaussImg, Size(3, 5), 0, 10);
	imwrite(".\\imagefiles\\GaussImg.jpg", GaussImg);
	cout << "show the image filtered by gaussian " << endl;
	imshow("GaussImg", GaussImg);

	// use median filter
	Mat MedImg;
	medianBlur(img, MedImg, 7);
	cout << "show the image filtered by median " << endl;
	imshow("MedImg", MedImg);
	imwrite(".\\imagefiles\\MedImg.jpg", MedImg);

	// use mean filter
	Mat MeanImg;
	blur(img, MeanImg, Size(3, 5));
	cout << "show the image filtered by mean " << endl;
	imshow("MeanImg", MeanImg);

}

int UseFilter2D(const Mat& src, Mat&dst) {
	dst = src.clone();
	Mat kern = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	filter2D(src, dst, src.depth(), kern);
	imshow("filter2D", dst);

	return 0;
}

int TestFilterFuns()
{
	cout << endl << "show the original image. " << endl;
	Mat img = imread(".\\imagefiles\\ali.jpg");
	if (img.empty()) {
		cout << "can not load image. " << endl;
	}
	else {
		imshow("original a li", img);
		waitKey();
	}

	// 测试几个常用滤波
	DifferentFilters(img);

	// 利用 filter2D 函数进行滤波
	Mat img2D;
	UseFilter2D(img, img2D);
	cout << "利用 filter2D 函数进行滤波的结果" << endl << endl;
	waitKey();
	return 0;
}

