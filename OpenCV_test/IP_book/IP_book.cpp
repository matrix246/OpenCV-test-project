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

void show_initialization(void){
	cout<<endl<<
		"展示 Mat的用法，每天都要看一下。"<<endl;
	// initialization of Mat
	int m = 300;
	int n = 200;
	Mat m1 = Mat::zeros(m,n,CV_8U);
	m1 = 255*Mat::eye(Size(m,m),CV_8U);
	imshow("m1",m1);

	// 利用 函数获取 结构元
	Mat ker = getStructuringElement(MORPH_CROSS,Size(3,3),Point(0,0));
	cout << endl<<
		"to_string(ker.at<uchar>(Point(x,y))) is:" <<endl;
	cout << "注意:这里不知道为什么，结构元不能直接显示成数字，"<<endl;
	cout <<" 因此，把每个元素转换成 string 然后再显示"<<endl;
	for (int y=0; y < ker.rows; y++)
	{
		for (int x = 0; x < ker.cols; x++)
		{
			cout << to_string(ker.at<uchar>(Point(x,y))) <<" ";
		}
		cout <<endl;
	}


	cout <<endl
		<< "利用 Scalar 对Mat 进行赋值"<<endl;
	Mat roi(Size(10,10),CV_8UC3);
	roi = Scalar(0,255,0);
	imshow("with box",roi);

	Mat m2(Size(10,10),CV_8U);
	m2 = 20;
	imshow("m2",m2);

}

void show_display(void){
	cout <<endl<<"注意:这里初始化的时候使用的是 double"<<endl;
	cout<<" 因此，在调用 at 和 ptr 的时候也需要指定 为 double "<<endl;
	Mat m2 = (Mat_<double>(3,3)<<1,2,3,4,5,6,7,8,9);
	cout << "(Mat_<double>(3,3)<<1,2,3,4,5,6,7,8,9) is: " <<endl;
	cout << "print by:  m2.at<double>(Point(x,y)) "<<endl;
	for (int y=0; y < m2.rows; y++)
	{
		for (int x = 0; x < m2.cols; x++)
		{
			cout << m2.at<double>(Point(x,y)) <<" ";
		}
		cout <<endl;
	}

	cout << "print by:  m2.at<double>(i,j) "<<endl;
	for (int i = 0; i < m2.rows; i++)
	{
		for (int j = 0; j < m2.cols; j++)
		{
			cout << m2.at<double>(i,j)<<" ";
		}
		cout <<endl;
	}

	cout << "print by:  double* p_m2 = m2.ptr<double>(y); "<<endl;
	cout << "           cout << p_m2[x] "<<endl;
	for (int y =0; y < m2.rows; y++)
	{
		double* p_m2 = m2.ptr<double>(y);
		for (int x = 0; x < m2.cols; x++)
		{
			cout << p_m2[x]<<" ";
		}
		cout <<endl;
	}
}

void show_diff_type(void){
	int m = 300;
	int n = 200;
	Mat m1 = Mat::zeros(m , n , CV_8UC2);
	cout << "m1.type() is: " << m1.type()<<endl;

	Vec2b pixel;
	pixel[0] = 255;
	pixel[1] = 0;

	// 这里得到的结果应该是只有右上角为白色，其他地方为黑色
	for (int y=0; y < m1.rows; y++)
		for (int x = y; x < m1.cols; x++)
			m1.at<Vec2b>(Point(x,y)) = pixel;


	cout << endl
		<<"imshow 只能展示通道为 1,3,4 的图像，这里 m1 只有两个通道"<<endl;
	cout << "因此，先利用 split 将 m1 拆开，然后只展示 第一层"<<endl;

	Mat mv[2];
	split(m1,mv);
	imshow("m1",mv[0]);

}

void test_reshape(void){
	int m = 300;
	int n = 200;
	Mat m1 = Mat::zeros(m , n , CV_8U);

	m1 = (Mat_<uchar>(3,3)<<1,2,3,4,5,6,7,8,9);
	// reshape Mat
	Mat m2 = m1.reshape(0,1);
	cout<<"size of m2 is: "<<m2.cols<<endl;
	for (int i = 0; i < m2.cols; i++)
		cout << to_string(m2.at<uchar>(i)) << "  ";
	cout <<endl
		<< "上面显示的结果表明 reshape 是按  行  进行 reshape 的。 "<<endl;
}

void test_type(void){
	int m = 3;
	int n = 2;
	cout <<"m1 初始化的时候虽然用了 CV_8U,但是 前面乘了一个 -1"<<endl;
	cout <<"因此 m1 的 type() 仍然是 0 "<<endl;
	cout <<"不论在输出的时候使用 uchar，还是 char 都全部为 0 "<<endl;

	Mat m1 = -1*Mat::ones(m,n,CV_8U);
	cout <<"m1.type() is: "<< m1.type()<<endl;
	cout <<endl<<"利用 m1.at<uchar>(i,j) 输出 得到的结果"<<endl;
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << to_string(m1.at<uchar>(i,j))<<" ";
		cout <<endl;
	}
	cout <<endl<<"利用 m1.at<char>(i,j) 输出 得到的结果"<<endl;
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << to_string(m1.at<char>(i,j))<<" ";
		cout <<endl;
	}
	cout <<endl;

	cout <<"m1 使用 CV_8S 初始化"<<endl;
	cout <<"m1 的 type() 是 1 "<<endl;
	cout <<"使用 uchar 输出的结果是 255"<<endl;
	cout <<"使用 char 输出的结果是 -1 "<<endl;

	m1 = -1*Mat::ones(m,n,CV_8S);
	cout <<"m1.type() is: "<< m1.type()<<endl;
	cout <<endl<<"利用 m1.at<uchar>(i,j) 输出 得到的结果"<<endl;
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << to_string(m1.at<uchar>(i,j))<<" ";
		cout <<endl;
	}
	cout <<endl<<"利用 m1.at<char>(i,j) 输出 得到的结果"<<endl;
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << to_string(m1.at<char>(i,j))<<" ";
		cout <<endl;
	}

}

void test_ROI(){
	Mat img = imread(".\\chp09\\Fig0941(a)(wood_dowels).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}
	imshow("nail",img);
	Mat cat = imread(".\\chp09\\cat.jpg");

	cout<<endl
		<<"指定感兴趣区域，两种方法"<<endl;
	Mat ROI =  img(Rect(40,40,cat.cols,cat.rows));
	//Mat ROI(img,Rect(40,40,cat.cols,cat.rows));

	// 截取roi 区域
	imshow("roi",ROI);

	cout<<endl
		<<"将猫放到感兴趣区域，两种方法"<<endl;
	//cat.copyTo(ROI);
	cat.copyTo(ROI,cat);
	imshow("nail with cat",img);


	// 在图像中画出 矩形
	rectangle(img,Rect(240,240,cat.cols,cat.rows),Scalar(0,0,255));
	imshow("with rectangle box",img);

	cout <<endl
		<< "利用 Rect 保存方框，然后使用"<<endl;
	Rect r1 = Rect(100,0,200,200);
	rectangle(img,r1,Scalar(0,0,255));
	imshow("with rectangle box 2",img);
}


void must_read_Mat(void){

	//show_initialization();
	//
	//show_display();

	//show_diff_type();

	//test_type();

	//test_reshape();

	test_ROI();
}

int main()
{

	//Morphology_Operate();

	//Gray_Morphology();

	//chp09_HomeWork();

	// chapter 10

	//Line_Point_dection();

	//must_read_Mat();

	//Seg_word_1();

	//Seg_word_2();

	Template_match_1();


	waitKey();
	system("pause");
	return 0;
}
