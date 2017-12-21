#include "stdafx.h"
#include "TestHeader.h"

using namespace std;
using namespace cv;

void TestCanny(const Mat& img) {

	imshow("original image", img);

	Mat edges;
	Canny(img, edges, 111, 112);
	imshow("color: edges with threshold 111 and 112", edges);

	Canny(img, edges, 70, 112);
	imshow("color: edges with threshold 70 and 112", edges);
	cout << "注意这里两个阈值，对结果的影响较大" << endl;
	cout << "threshold1 和 threshold2 控制了得到的边界的精细程度" << endl;

	Mat Img_gray;
	cvtColor(img, Img_gray, CV_BGR2GRAY);
	Canny(Img_gray, edges, 111, 112);
	imshow("gray: edges with threshold 111 and 112", edges);
	cout << "利用 canny 对灰度图像和彩色图像处理，结果也不一样" << endl;

	waitKey();
}

void TestConverTo(const Mat& src) {
	Mat img = src.clone();
	double alpha, beta;
	alpha = 1.5;
	beta = 2;

	Mat dst = img.clone();
	img.convertTo(dst, img.type(), alpha, beta);
	string sname = "use converTo: alpha(对比度) = " + to_string(alpha) +
		"  beta(亮度) = " + to_string(beta);
	imshow(sname, dst);

	MyConcerTo(src, dst, alpha, beta);
	string sname2 = "use my own fun: alpha(对比度) = " + to_string(alpha) +
		"  beta(亮度) = " + to_string(beta);
	imshow(sname2, dst);
	waitKey();
}

void MyConcerTo(const Mat& src, Mat& dst, double alpha, double beta) {
	Mat img = src.clone();

	if (img.channels() == 3)
	{
		for (int i = 0; i < img.rows; i++)
		{
			Vec3b* p_vec3b1 = img.ptr<Vec3b>(i);
			Vec3b* p_vec3b2 = img.ptr<Vec3b>(i);
			for (int j = 0; j < img.cols; j++)
			{
				for (int c = 0; c < img.channels(); c++)
				{
					p_vec3b2[j][c] = static_cast<uchar>(p_vec3b1[j][c] + beta);
				}
			}
		}
	}
	else if (img.channels() == 1)
	{
		for (int i = 0; i < img.rows; i++)
		{
			uchar* p_uchar1 = img.ptr<uchar>(i);
			uchar* p_uchar2 = dst.ptr<uchar>(i);
			for (int j = 0; j < img.cols; j++)
			{
				//saturate_cast 是为了防止数据溢出
				p_uchar2[j] = saturate_cast<uchar>(alpha*p_uchar1[j] + beta);
			}
		}
	}
	else {
		cerr << "the channels of img is not 1 or 3" << endl;
	}


}

int ChangeImage() {

	// load and show the original image
	Mat img = imread(".\\imagefiles\\ali.jpg");
	if (img.empty()) {
		cerr << "can not load image." << endl;
	}

	// normalize the image 
	Mat dst;
	double lambda = 0.41;

	// 测试canny 边缘检测
	// TestCanny(img);

	// 测试 converTo 成员函数
	TestConverTo(img);


	return 0;
}