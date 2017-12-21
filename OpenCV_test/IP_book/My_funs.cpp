#include "stdafx.h"
#include "IPbook.h"
#include "chp09.h"

using namespace std;

void Show_Four_subimage(const Mat& img1,const Mat& img2,const Mat& img3,const Mat& img4,String str){
	int mcols , mrows, tcols, trows;
	mcols = max(max(max(img1.cols , img2.cols) , img3.cols) , img4.cols);
	mrows = max(max(max(img1.rows , img2.rows) , img3.rows) , img4.rows);
	tcols = mcols * 2 + 40;
	trows = mrows * 2 + 40;

	Mat Many(trows , tcols , img1.type());

	Rect rect1(10 , 10 , mcols , mrows);
	Rect rect2(mcols + 20 , 10 , mcols , mrows);
	Rect rect3(10 , mrows + 20 , mcols , mrows);
	Rect rect4(mcols + 20 , mrows + 20 , mcols , mrows);

	img1.copyTo(Many(rect1));
	img2.copyTo(Many(rect2));
	img3.copyTo(Many(rect3));
	img4.copyTo(Many(rect4));

	namedWindow(str,WINDOW_NORMAL);
	imshow(str , Many);
}

void Print_Mat(const Mat& m){
	// channels must be 1
	if (m.channels()!=1)
	{
		cerr<<"the channels of m must be 1 "<<endl;
	}

	for (int i =0; i<m.rows; i++)
	{
		for (int j = 0; j < m.cols; j ++)
		{
			cout << to_string(m.at<uchar>(i,j)) <<"  ";
		}
		cout <<endl;
	}
	cout << endl;
}

// 这个函数有问题，具体是什么还没有查清楚
void My_Reconstruct_Open(const Mat& src,Mat& dst,Mat& ker, int n){

	Mat F;// 利用 ker  对 src 腐蚀 n 次得到的 标记图像 F ；
	morphologyEx(src, F,MORPH_ERODE,ker,Point(-1,-1),n);


	// 对 F 进行  测地膨胀
	morphologyEx(F,dst,MORPH_DILATE,ker);
	F = min(dst , src);

	Mat Fk(F.rows, F.cols, F.type());
	bool stop = sum(Fk) == sum(F);


	// 当 两次结果不一致的时候就一直迭代
	while(stop != 1){
		Fk = F;

		morphologyEx(F,dst,MORPH_DILATE,ker);
		F = min(dst ,src);

		cout << "F is " <<endl;
		Print_Mat(F);
		cout << "Fk is " <<endl;
		Print_Mat(Fk);

		stop = sum(Fk) == sum(F);
		system("pause");
	}
	dst = F;
}
