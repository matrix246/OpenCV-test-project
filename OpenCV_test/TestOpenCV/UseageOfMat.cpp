#include "stdafx.h"

using namespace std;
using namespace cv;

int ConstructMat() {

	Mat mm = imread(".\\imagefiles\\FaceLight.jpg");
	//cout << "src.data is: " << img.data << endl;
/*
	int matSize[] = { 3,4,5 ,2};
	Mat mm( 3,matSize, 6);	*/


	cout << "mm.rows is: " << mm.rows << endl;
	cout << "mm.cols is: " << mm.cols << endl;
	cout << "mm.total() is: " << mm.total() << endl;
	cout << "mm.type() is: " << mm.type() << endl;
	cout << "mm.size is: " << mm.size << endl;
	cout << "mm.dims is: " << mm.dims << endl << endl;

	cout << "mm.step[0] is: " << mm.step[0] << endl;
	cout << "mm.step[1] is: " << mm.step[1] << endl;
	cout << "mm.step[2] is: " << mm.step[2] << endl << endl;

	cout << "mm.size[0] is: " << mm.size[0] << endl;
	cout << "mm.size[1] is: " << mm.size[1] << endl;
	cout << "mm.size[2] is: " << mm.size[2] << endl << endl;

	cout << "mm.step1(0) is: " << mm.step1(0) << endl;
	cout << "mm.step1(1) is: " << mm.step1(1) << endl;
	cout << "mm.step1(2) is: " << mm.step1(2) << endl << endl;


	cout << "mm.elemSize() is: " << mm.elemSize() << endl;
	cout << "mm.elemSize1() is: " << mm.elemSize1() << endl;

	return 0;

}

int ShowDetailsOfMat(const Mat& src) {

	// 详细信息参考
	// ref:http://blog.csdn.net/holybin/article/details/17751063

	cout << "src.type() is: " << src.type() << endl;
	cout << "src.channels() is: " << src.channels() << endl;
	cout << "src.size is: " << src.size << endl;
	cout << "src.rows is: " << src.rows << endl;
	cout << "src.cols is: " << src.cols << endl;
	cout << "src.allocator is: " << src.allocator << endl;
	cout << "src.CONTINUOUS_FLAG is: " << src.CONTINUOUS_FLAG << endl;
	cout << "src.AUTO_STEP is: " << src.AUTO_STEP << endl << endl;


	//cout << "src.data is: " << src.data << endl;
	cout << "src.dataend is: " << src.dataend << endl;
	cout << "src.datalimit is: " << src.datalimit << endl;
	//cout << "src.datastart is: " << src.datastart << endl;
	cout << "src.depth() is: " << src.depth() << endl;
//	cout << "src.DEPTH_MASK is: " << src.DEPTH_MASK << endl;
	//cout << "src.diag() is: " << src.diag() << endl;
	cout << "src.dims is: " << src.dims << endl << endl;



	cout << "src.elemSize() is: " << src.elemSize() << endl;
	cout << "src.elemSize1() is: " << src.elemSize1() << endl;
	cout << "src.empty() is: " << src.empty() << endl;
	cout << "src.flags is: " << src.flags << endl;
//	cout << "src.getDefaultAllocator() is: " << src.getDefaultAllocator() << endl;
//	cout << "src.getStdAllocator() is: " << src.getStdAllocator() << endl;
	cout << "src.isContinuous() is: " << src.isContinuous() << endl;
	cout << "src.isSubmatrix() is: " << src.isSubmatrix() << endl;
//	cout << "src.MAGIC_MASK is: " << src.MAGIC_MASK << endl << endl;


	cout << "src.MAGIC_VAL is: " << src.MAGIC_VAL << endl;
	//cout << "src.row(0) is: " << src.row(0) << endl;
	//cout << "src.rowRange(0,1) is: " << src.rowRange(0,1) << endl;
	cout << "src.size is: " << src.size << endl;
	cout << "src.step is: " << src.step << endl;
	cout << "src.step1() is: " << src.step1() << endl;
	cout << "src.SUBMATRIX_FLAG is: " << src.SUBMATRIX_FLAG << endl;
	//cout << "src.rows is: " << src.t() << endl;
	cout << "src.total() is: " << src.total() << endl;
	cout << "src.type() is: " << src.type() << endl;
//	cout << "src.TYPE_MASK is: " << src.TYPE_MASK << endl;
//	cout << "src.u is: " << src.u << endl;

	Vec3b pixel;
	src.colRange(1, 2);
	return 0;
}

void InitialMat() {
	Mat d = (Mat_<double>(2, 3) << 1, 2, 3, 8, 9, 10);
	cout << "d=\n " << d << endl;
	cout << "d.rows= " << d.rows << endl;
	cout << "d.cols= " << d.cols << endl;
	// 利用 at 取元素
	cout << "d（2,1）=  " << d.at<double>(1, 0) << endl;
	cout << "d.at<double>(Point(1,0)) is " << d.at<double>(Point(1,0))<<endl;
	// 利用指针取元素
	double* p = d.ptr<double>(1);
	cout << "d（2,1）= " << p[0] << endl; 
}

int UseageOfMat() {

	// load and show the original image
	Mat img = imread(".\\imagefiles\\FaceLight.jpg");
	if (img.empty()) {
		cerr << "can not load image." << endl;
	}

	// 展示 Mat 中的一些函数
	//ShowDetailsOfMat(img);

	//ConstructMat();

	InitialMat();
	
	system("pause");

	return 0;
}
