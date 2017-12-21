#include "stdafx.h"

using namespace std;
using namespace cv;

void ChangeByAt(const Mat& img) {
	Mat src = img.clone();
	if (src.channels() == 1) {
		for (int i = 0; i < src.rows;i++) {
			for (int j = 0; j < src.cols / 2;j++) {
				src.at<uchar>(i, j) = 0;
			}
		}
	} 
	else if (src.channels() == 3) {
		Vec3b pixel;
		pixel[0] = 255;
		pixel[1] = 255;
		pixel[2] = 0; 
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols / 2; j++) {
				src.at<Vec3b>(i, j) = pixel;
			}
		}
	}
	else {
		cerr << "the channels of image is not right." << endl;
	}

	imshow("change by atom", src);
	waitKey();

}

void ChangeByPtr(const Mat& img) {
	Mat src = img.clone();
	if (src.channels() == 1) {
		for (int i = 0; i < src.rows; i++) {
			uchar* p = src.ptr<uchar>(i);
			for (int j = 0; j < src.cols / 2; j++) {
				p[j] = 0;
			}
		}
	}
	else if (src.channels() == 3) {
		Vec3b pixel;
		pixel[0] = 255;
		pixel[1] = 255;
		pixel[2] = 0;
		for (int i = 0; i < src.rows; i++) {
			Vec3b* p = src.ptr<Vec3b>(i);
			for (int j = 0; j < src.cols / 2; j++) {
				p[j] = pixel;
			}
		}
	}
	else {
		cerr << "the channels of image is not right." << endl;
	}

	imshow("change by pointer", src);
	waitKey();

}

int DisplayLocation(const Mat& img) {

	Mat src = img.clone();
	if (src.channels() == 1) {
		cout << "the channels is not 3. " << endl;
		return 0;
	}

	Vec3b pixel;
	pixel[0] = 0;// B
	pixel[1] = 255;// G
	pixel[2] = 255;// R

	for (int i = 0; i < src.rows / 2; i++) {
		for (int j = 0; j < src.cols / 5; j++) {
			src.at<Vec3b>(i, j) = pixel;
		}
	}

	imshow("modified image. ", src);
	cout << "图片中出现黄色说明，opencv中通到是按照 BGR 的顺序排列的。" << endl;
	cout << "在图片左上角出现黄色细条纹说明，opencv中Mat的  坐标轴原点  位于  图片左上角" << endl;
	cout << "         从上往下依次是 第 0,1,2,3，... 行。 " << endl;
	waitKey();
	return 0;
}

// “浅”拷贝  与 “深”拷贝
// ref: http://blog.csdn.net/qq_23968185/article/details/51242686
void DeepAndShadowCopy(void) {
	// shadow copy
	Mat img = imread(".\\imagefiles\\ali.jpg");
	if (img.empty()) {
		cerr << "can not load image." << endl;
	}
	imshow("before flip img2", img);
	Mat img2 = img;
	flip(img2, img2, 0);
	imshow("after flip img2", img);
	waitKey();
	cout << endl;
	cout << "直接赋值并没有创建新的 Mat 数据，只是引用，" << endl;
	cout << "因此，改变新的 Mat， 原来的 Mat 也改变了" << endl;
	cout << "这个属于“浅”拷贝" << endl << endl;;

	// deep copy
	img = imread(".\\imagefiles\\ali.jpg");
	if (img.empty()) {
		cerr << "can not load image." << endl;
	}
	imshow("before flip img3", img);
	Mat img3 = img.clone();
	flip(img3, img3, 0);
	imshow("after flip img3", img);
	waitKey();
	cout << "要创建新的 Mat 需要使用函数，属于“深”拷贝" << endl;
	cout << "这里使用了 .colne() 函数，实现“深拷贝”" << endl;
}


int imreadAndChangePixel() {
	// read image 
	/*（2）函数的声明格式：
Mat imread( const string& filename,int flags=1 );

（3）参数说明：
filename : 被读取的图像的名字
flags ： 说明读取图像的数据类型
如果flags>0 , 那么是把图像加载成3通道的彩色图像（注意：默认被加载成了一副彩色图像）
如果flags=0,那么把图像加载成灰度图（单通道的图像）
如果flags<0,那么如果图像本身是彩色图，就加载成彩色图，如果图像本身是灰度图就加载成灰度图。
如果图像加载失败，那么imread会返回一个空矩阵(Mat::data == NULL)。*/

	Mat img = imread(".\\imagefiles\\ali.jpg",1);
	if (img.empty()) {
		cerr << "can not load image." << endl;
	}

	// change pixel by atom "at"
	ChangeByAt(img);
	// change pixel by pointer	"ptr"
	ChangeByPtr(img);
	// 理解opencv中 BGR的顺序，理解 坐标摆放的顺序
	DisplayLocation(img);
	// 理解 opencv 中 Mat 的“浅拷贝” 与 “深拷贝”
	DeepAndShadowCopy();

	system("pause");
	return 0;
}