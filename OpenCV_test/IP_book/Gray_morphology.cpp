#include "stdafx.h"
#include "IPbook.h"
#include "My_funs.h"
#include "chp09.h"

using namespace std;


void Fig_X_Ray(){

	Mat img = imread(".\\chp09\\Fig0935(a)(ckt_board_section).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}

	imshow("x ray",img);

	Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(5,5));
	//Print_Mat(ker);

	Mat dst;
	morphologyEx(img,dst,MORPH_ERODE,ker);
	imshow("after erode",dst);

	morphologyEx(img,dst,MORPH_DILATE,ker);
	imshow("after dilate",dst);

	ker = getStructuringElement(MORPH_ELLIPSE,Size(7,7));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("after open",dst);

	ker = getStructuringElement(MORPH_ELLIPSE,Size(11,11));
	morphologyEx(img,dst,MORPH_CLOSE,ker);
	imshow("after close",dst);
}

void Fig_Cloud(){
	Mat img = imread(".\\chp09\\Fig0938(a)(cygnusloop_Xray_original).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("cloud",img);

	Mat dst;
	Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(5,5));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	morphologyEx(dst,dst,MORPH_CLOSE,ker);
	imshow("after open and close with radius 2",dst);

	ker = getStructuringElement(MORPH_ELLIPSE,Size(7,7));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	morphologyEx(dst,dst,MORPH_CLOSE,ker);
	imshow("after open and close with radius 3",dst);

	ker = getStructuringElement(MORPH_ELLIPSE,Size(11,11));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	morphologyEx(dst,dst,MORPH_CLOSE,ker);
	imshow("after open and close with radius 5",dst);

}

void Fig_CT_bone(){
	Mat img = imread(".\\chp09\\Fig0939(a)(headCT-Vandy).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("cloud",img);

	Mat dst;
	Mat ker = getStructuringElement(MORPH_RECT,Size(3,3));
	morphologyEx(img,dst,MORPH_DILATE,ker);
	imshow("after dilate",dst);

	morphologyEx(img,dst,MORPH_ERODE,ker);
	imshow("after erode",dst);

	morphologyEx(img,dst,MORPH_GRADIENT,ker);
	imshow("after gradient",dst);
}

void Fig_Rice(){
	Mat img = imread(".\\chp09\\Fig0940(a).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("Rice",img);

	Mat mv[3];
	// 将多通道的图像分成单个通道的图像
	split(img,mv);

	Mat dst;
	double thresh = 90;
	double maxval = 255;
	// 注意 threshold 中的otsu 只能处理 8-bit 的图像
	threshold(mv[0],dst,thresh,maxval,THRESH_OTSU);
	imshow("using otsu",dst);

	Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(91,91));

	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("after open with 40 radius",dst);

	dst = img - dst;
	imshow("after dilate",dst);

	split(dst,mv);
	threshold(mv[0],dst,thresh,maxval,THRESH_OTSU);
	imshow("after dilate using otsu",dst);

}

void Fig_Nail(){
	Mat img = imread(".\\chp09\\Fig0941(a)(wood_dowels).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("nail",img);
	Mat dst;

	int radius = 5;
	Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	morphologyEx(dst,dst,MORPH_CLOSE,ker);
	imshow("after open and close with 5 radius",dst);
	 
	radius = 10;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("after open 10 radius",dst);

	radius = 20;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("after open 20 radius",dst);

	radius = 25;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("after open 25 radius",dst);

	radius = 30;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("after open 30 radius",dst);

}

void test_Granulometry(){
	/*对 书中 P434页，粒度测定的理解
	当以用一个尺寸小于待测物体的 se 进行 open 之后
	物体变小
	当以用一个尺寸 远大于 待测物体的 se 进行 open 之后
	物体消失

	当以用一个尺寸 等于 待测物体的 se 进行 open 之后
	物体不变
	*/
	Mat img = Mat::zeros(10,10,CV_8U);

	int radius = 2;
	Mat img2 = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	Mat mv[3];
	split(img2,mv);
	img2 = mv[0];

	Mat ROI = img(Rect(2,2,img2.cols,img2.rows));

	img2.copyTo(ROI,img2);

	Print_Mat(img);
	cout <<"img" <<endl;


	Mat dst;
	radius = 1;
	Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	Print_Mat(dst);
	cout <<"dst with radius 1" <<endl;

	radius = 2;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	Print_Mat(dst);
	cout <<"dst with radius 2" <<endl;

	radius = 3;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_OPEN,ker);
	Print_Mat(dst);
	cout <<"dst with radius 3" <<endl;

}


void Fig_Dots(){
	Mat img = imread(".\\chp09\\Fig0943(a)(dark_blobs_on_light_background).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("dots",img);

	Mat dst;
	int radius = 30;
	Mat ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(img,dst,MORPH_CLOSE,ker);
	imshow("after close with radius 30",dst);

	radius = 60;
	ker = getStructuringElement(MORPH_ELLIPSE,Size(2*radius+1,2*radius+1));
	morphologyEx(dst,dst,MORPH_OPEN,ker);
	imshow("after close and open with radius 60",dst);

	ker = Mat::ones(3,3,CV_8U);
	morphologyEx(dst,dst,MORPH_GRADIENT,ker);
	imshow("boundry",dst);

	imshow("dots with boundry",dst + img);

}

void Fig_Calculator(){
	Mat img = imread(".\\chp09\\Fig0944(a)(calculator).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("calculator",img);

	Mat dst;
	Mat ker = Mat::ones(1,71,CV_8U);

	// 重建开操作
	int n = 2;
	My_Reconstruct_Open(img,dst,ker,n);
	imshow("image (b)",dst);
	Mat image_d  = img - dst;
	imshow("image (d)" , image_d);

	ker = Mat::ones(1,11,CV_8U);
	My_Reconstruct_Open(image_d,dst,ker,1);
	imshow("image (f)" , dst);

	ker = Mat::ones(1,21,CV_8U);
	morphologyEx(dst,dst,MORPH_OPEN,ker);
	imshow("image (g)" , dst);

	Mat image_h  = min(image_d,dst);
	imshow("image (h)" , image_h);
	

	// 开操作
	ker = Mat::ones(1,71,CV_8U);
	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("image (c)",dst);
	imshow("image (e)" , img - dst);

}


void test_min(){
	Mat img1 = imread(".\\chp09\\gril.jpg");
	Mat img2 = imread(".\\chp09\\gril2.jpg");

	Mat minimg = min(img1,img2);
	Mat maximg = max(img1,img2);

	String str = "图1，图2，求最小，求最大";
	// 同时显示 4 张图片
	Show_Four_subimage(img1,img2,minimg,maximg,str);

	// 测试两幅图是否相等
	Scalar ss =	sum(img1);
	Scalar ss2 = sum(img1);

	bool diff = ss == ss2;


	cout <<"ss is:" <<diff<<endl;

}

void Gray_Morphology(){


	//Fig_X_Ray();
	//Fig_Cloud();
	//Fig_CT_bone();
	//Fig_Rice();

	//Fig_Nail();

	//test_Granulometry();
	//test_ROI();

	//Fig_Dots();
	//test_min();
	//Fig_Calculator();





	waitKey();
}