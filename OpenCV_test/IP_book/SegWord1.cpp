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
// 注意，当 图像存在旋转（words_angle) 或者
// 字体大小不一致(words_not_equal)时，直方图投影的方法失效

void test_pointer(int* a, int b, int& c){
	int d = 200;
	a = &d;
	b = 200;
	c = 200;
	cout << "*a is: " << *a <<endl;
	cout << "b is: " << b <<endl;
	cout << "c is: " << c <<endl<<endl;

}
void use_test_pointer(void){
	int* a;
	int d = 0;
	a = &d;
	int b = 0;
	int c = 0;
	cout << "*a is: " << *a <<endl;
	cout << "b is: " << b <<endl;
	cout << "c is: " << c <<endl<<endl;
	// 第一个输入是 pointer 类型的，使用的时候必须初始化指针
	// a = &d;
	test_pointer(a,b,c);
	// 使用pointer 指针指向的类型也可以 &d
	test_pointer(&d,b,c);

	cout << "*a is: " << *a <<endl;
	cout << "b is: " << b <<endl;
	cout << "c is: " << c <<endl;
}


void test_list(void){
	Mat img = imread(".\\chp09\\Fig0941(a)(wood_dowels).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("nail",img);

	Rect r1 = Rect(0,0,100,100);
	Rect r2 = Rect(20,20,100,100);
	Rect r3 = Rect(40,40,100,100);
	Scalar co = Scalar(0,0,255);

	list<Rect> blocks; // 定义一个链表
	list<Rect>::iterator p_list; // 定义一个链表中的迭代器

	blocks.push_back(r1);
	blocks.push_back(r2);
	blocks.push_back(r3);

	for (p_list = blocks.begin(); p_list != blocks.end(); p_list++)
		rectangle(img,*p_list,co);

	imshow("image with box", img);

}


void Find_begin_end_len(Mat h_vec,Mat& locations,int& count, int width){
	// locations 为 3*N 大小的 全零的 Mat，
	// 经过这个函数处理之后，变成 3*count 大小的矩阵

	if (locations.type() != 4 || h_vec.type() != 4)
		cout <<"locations and h_vec must be type of CV_32S"<<endl;

	// 将 h_vec 变成一个  一行多列 的矩阵，便于处理
	if (h_vec.rows != 1)
		transpose(h_vec,h_vec);

	int N = h_vec.cols;
	int begin, end, len;
	count = 0;
	int n = 0;  // number of pixels in h_vec[i]

	for (int i = 0; i < N; i++)
	{
		//cout <<" i is: "<< i<<endl;
		n = h_vec.at<int>(0,i);
		if (n != 0)
		{
			begin = i;
			for (int j = i; j < N; j++)
			{
				n = h_vec.at<int>(0,j);
				if (n == 0)
				{
					end = j-1;
					len = end - begin;
					if (len >= width)
					{
						locations.at<int>(0,count) = begin;
						locations.at<int>(1,count) = end;
						locations.at<int>(2,count) = len;
						count = count + 1;
						//// test if the code is right
						//cout <<" begin is: "<< begin<<endl;
						//cout <<" end is: "<< end<<endl;
						//cout <<" len is: "<< len<<endl;
						//cout <<" count is: "<< count<<endl;

					}
					i = j;
					break;
				}
			}

		}

	}

}


void Seg_word_1(void){
	Mat img = imread(IMG_PATH);
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);


	// step 1) 对图像二值化，这里因为使用 otsu 必须是单通道，
	//所以先将图像变成 单通道的图像
	Mat gray_img;
	cvtColor(img,gray_img,CV_BGR2GRAY,1);

	Mat binary_img;
	threshold(gray_img,binary_img,90,255,THRESH_OTSU);
	binary_img = 255 - binary_img;
	imshow("binary image by otsu", binary_img);

	// step 2) 对二值化之后的图像进行水平方向投影（找到不同行）
	Mat hist_ver;
	reduce(binary_img/255,hist_ver,1,CV_REDUCE_SUM,CV_32S);

	int width = 5;
	int totaln = max(hist_ver.rows,hist_ver.cols);
	Mat locations = Mat::zeros(3,totaln,CV_32S);
	int count = 0;
	Find_begin_end_len(hist_ver,locations,count,width);


	// step 3）利用2）得到的结果对二值化图像切割，
	// 然后对每一行进行垂直方向的投影（找到每一行内的不同文字）
	Mat line;
	int x,y,height;
	x = 0;
	Mat hist_hor;
	Mat locations2 = Mat::zeros(3,totaln,CV_32S);

	list<Rect> blocks; // 定义一个链表
	list<Rect>::iterator p_list; // 定义一个链表中的迭代器
	int count2 = 0;
	Rect r1;
	int bx,by,bwid,bhei;
	width = 2;

	for (int i = 0; i < count; i++)
	{
		y = locations.at<int>(0,i);
		height = locations.at<int>(2,i);
		line = binary_img(Rect(x , y , binary_img.cols,height));
		reduce(line/255,hist_hor,0,CV_REDUCE_SUM,CV_32S);
		Find_begin_end_len(hist_hor,locations2,count2,width);

		// 利用链表存储 Rect 区域
		for (int j = 0; j < count2; j++)
		{
			bx = locations2.at<int>(0,j);
			by = locations.at<int>(0,i);
			bwid = locations2.at<int>(2,j);
			bhei = locations.at<int>(2,i);

			r1 = Rect(bx,by,bwid,bhei);
			blocks.push_back(r1);
		}

	}

	// step 4) 利用 2）和3）得到的结果画出方框。

	Scalar color  = Scalar(0, 0, 255);
	for (p_list = blocks.begin(); p_list != blocks.end(); p_list++)
		rectangle(img,*p_list,color );

	imshow("image with box", img);

}
