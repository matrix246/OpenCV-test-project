#include "stdafx.h"
#include "My_funs.h"
#include "IPbook.h"
#include "chp09.h"

using namespace std;

void Morp_Erode(){
	Mat img = imread(".\\chp09\\Fig0905(a).tif");
	if (img.empty()){
		cerr <<"can not read the image"<<endl;
	}
	imshow("original image",img);

	Mat dst;

	int dilation_size = 3;
	Mat ker1 = getStructuringElement(MORPH_CROSS ,
		Size(2*dilation_size + 1, 2*dilation_size+1),
		Point( dilation_size,dilation_size));

	erode(img,dst,ker1);
	imshow("erode image by cross",dst);

	Mat ker2 = Mat::eye(4,4,CV_8U);
	erode(img,dst,ker2);
	imshow("erode by eye matrix", dst);

}

void Morp_Dilate(){
	Mat img = imread(".\\chp09\\Fig0905(a).tif");
	if (img.empty()){
		cerr <<"can not read the image"<<endl;
	}
	imshow("original image",img);

	Mat dst;
	Mat ker1 = Mat::eye(4,4,CV_8U);
	dilate(img,dst,ker1);
	imshow("dilate by kernel",dst);

	Mat img2 = imread(".\\chp09\\Fig0907(a).tif");
	Mat ker2 = getStructuringElement(MORPH_CROSS,Size(3,3));
	dilate(img2,dst,ker2);
	imshow("word image before dilate",img2);
	imshow("dilate of word",dst);

}
void Test_MorphologyEx(){
	Mat img = imread(".\\chp09\\Fig0911(a)(noisy_fingerprint).tif");
	if (img.empty())
	{
		cerr<<"can not read image."<<endl;
	}
	imshow("original image",img);
	// test open
	Mat dst;
	Mat ker = Mat::ones(3,3,CV_8U);

	morphologyEx(img,dst,MORPH_OPEN,ker);
	imshow("MORPH_OPEN",dst);

	morphologyEx(img,dst,MORPH_CLOSE,ker);
	imshow("MORPH_CLOSE",dst);

	morphologyEx(img,dst,MORPH_ERODE,ker);
	imshow("MORPH_ERODE",dst);

	morphologyEx(img,dst,MORPH_GRADIENT,ker);
	imshow("MORPH_GRADIENT",dst);

	morphologyEx(img,dst,MORPH_TOPHAT,ker);
	imshow("MORPH_TOPHAT",dst);

	morphologyEx(img,dst,MORPH_BLACKHAT,ker);
	imshow("MORPH_BLACKHAT",dst);


}

void Extract_edge(){
	Mat img = imread(".\\chp09\\Fig0914(a).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image",img);
	Mat dst,ker;
	ker = Mat::ones(3,3,CV_8U);

	morphologyEx(img,dst,MORPH_ERODE,ker);
	dst = img - dst;
	imshow("edge",dst);

	morphologyEx(img,dst,MORPH_GRADIENT,ker);
	imshow("edge by gradient",dst);
}

void Checken_0918(){
	Mat img = imread(".\\chp09\\Fig0918(a).tif");
	if (img.empty())
	{
		cerr<<"can not read image." <<endl;
	}

	imshow("original image", img);

	Mat dst;
	double thresh,maxvalue;
	thresh = 205;
	maxvalue = 200;
	threshold(img,dst,thresh,maxvalue,THRESH_TOZERO);
	imshow("after threshold",dst);
	Mat ker = Mat::ones(5,5,CV_8U);
	morphologyEx(dst,dst,MORPH_ERODE,ker);
	imshow("after erode",dst);


}

void Move_Draft(){
	Mat img = imread(".\\chp09\\draft.jpg");
	Mat grayimg;
	cvtColor(img,grayimg,CV_BGR2GRAY);
	imshow("gray image",grayimg);

	double thresh = 200;
	double maxval = 255;
	threshold(grayimg,grayimg,thresh,maxval,THRESH_BINARY);
	imshow("after threshold",grayimg);

	grayimg = 255-grayimg;
	Mat ker = Mat::ones(3,3,CV_8U);
	ker = getStructuringElement(MORPH_CROSS,Size(3,3));
	ker = (Mat_<uchar>(2,2)<<0,0,1,1);
	morphologyEx(grayimg,grayimg,MORPH_DILATE,ker);
	imshow("after close",255-grayimg);
}

void Location_of_Anchor(){
	int d = 6;
	Mat A = Mat::eye(d,d,CV_8U);
	Mat B = (Mat_<uchar>(3,3)<<0,0,1,0,1,0,1,0,0);
	Mat dst;
	// ע�������ǹ���
	cout <<"����Ľ���Ǹ��� opencv �е�����ʽ�ӵõ���"<<endl;
	cout <<"�������ϸ������еĶ���õ��ģ�����"<<endl<<endl;

	// ����ê��λ�����Ͻ�
	cout << "�ṹԪΪ���ԽǾ���ê��λ��λ�����Ͻǣ����͵Ľ��"<<endl;
	dilate(A,dst,B,Point(2,0));
	Print_Mat(dst);

	cout << "�ṹԪΪ��λ����ê��λ�����½ǣ���ʴ�Ľ��"<<endl;
	B = Mat::eye(3,3,CV_8U);
	erode(A,dst,B,Point(0,2));
	Print_Mat(dst);

	loc_anchor();
}

void loc_anchor(){
	cout<< " ����˵�� ���� anchor ��  Point ������" <<endl;
	cout << "Point �еĵ�һ���� �� ������ " <<endl;
	cout << "		   �ڶ����� �� ������ " <<endl;
	
	int d = 5;
	Mat A = Mat::eye(d,d,CV_8U);
	cout <<endl<<"A ��ԭʼ��ʽ�� "<<endl;
	Print_Mat(A);

	Mat B = (Mat_<uchar>(3,3)<<0,0,1,0,0,1,0,0,1);
	Mat dst;

	cout <<endl<<"�����õĽṹԪ����ʽ"<<endl;
	Print_Mat(B);

	cout <<"��A  ���� ��ê��λ�����Ͻ� ֮��Ľ���� "<<endl;
	dilate(A , dst , B , Point(2,0));
	Print_Mat(dst);

	cout <<"��A  ��ʴ  ��ê��λ�����Ͻ�֮��Ľ���� "<<endl;
	erode(A , dst , B , Point(2,0));
	Print_Mat(dst);

}

void Test_hit(){
	Mat A = Mat::zeros(6,6,CV_8U);
	A.at<uchar>(2,2) = 1;
	A.at<uchar>(3,1) = 1;
	A.at<uchar>(1,3) = 1;

	// ����չʾ���ǻ��б任��һ��������
	// �� ���������ĽṹԪ����̫�������¼�ⲻ���κ�һ��
	// ȡ�������ע�ͣ�����չʾ�������
	//A.at<uchar>(2,4) = 1;
	//A.at<uchar>(3,3) = 1;
	//A.at<uchar>(4,2) = 1;
	Print_Mat(A);


	Mat B = (Mat_<uchar>(3,3)<<0,0,1,0,1,0,1,0,0);
	Mat A1,A2,R;

	morphologyEx(A,A1,MORPH_ERODE,B,Point(-1,-1));
	Print_Mat(A1);

	Mat B2 = (Mat_<uchar>(5,5)<<1,1,1,1,1,
								1,1,1,0,1,
								1,1,0,1,1,
								1,0,1,1,1,
								1,1,1,1,1);
	Print_Mat(1-A);
	morphologyEx(1-A,A2,MORPH_ERODE,B2,Point(-1,-1));
	Print_Mat(A2);

	R = A1&A2;
	Print_Mat(R);



}

void Fig_text(){
	Mat img = imread(".\\chp09\\Fig0929(a)(text_image).tif");
	Mat dst1,dst2,dst3;
	Mat ker = Mat::ones(51,1,CV_8U);

	morphologyEx(img,dst1,MORPH_ERODE,ker);
	morphologyEx(img,dst2,MORPH_OPEN,ker);
	My_Reconstruct_Open(img,dst3,ker,5);

	String str = "different open";
	Show_Four_subimage(img,dst1,dst2,dst3,str);

}


void Morphology_Operate(){
	// Morp_Erode(); // erode image and show result
	// Morp_Dilate(); // dilate image and show result

	//Test_MorphologyEx();


	//Extract_edge();

	//Checken_0918();

	//Move_Draft();

	//Location_of_Anchor();
	//loc_anchor();

	//Test_hit();
	//test_Granulometry();

	//Fig_Dots();

	//Fig_text();
	
	waitKey();

}