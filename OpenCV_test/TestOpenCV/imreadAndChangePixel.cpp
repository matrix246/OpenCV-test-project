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
	cout << "ͼƬ�г��ֻ�ɫ˵����opencv��ͨ���ǰ��� BGR ��˳�����еġ�" << endl;
	cout << "��ͼƬ���Ͻǳ��ֻ�ɫϸ����˵����opencv��Mat��  ������ԭ��  λ��  ͼƬ���Ͻ�" << endl;
	cout << "         �������������� �� 0,1,2,3��... �С� " << endl;
	waitKey();
	return 0;
}

// ��ǳ������  �� �������
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
	cout << "ֱ�Ӹ�ֵ��û�д����µ� Mat ���ݣ�ֻ�����ã�" << endl;
	cout << "��ˣ��ı��µ� Mat�� ԭ���� Mat Ҳ�ı���" << endl;
	cout << "������ڡ�ǳ������" << endl << endl;;

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
	cout << "Ҫ�����µ� Mat ��Ҫʹ�ú��������ڡ������" << endl;
	cout << "����ʹ���� .colne() ������ʵ�֡������" << endl;
}


int imreadAndChangePixel() {
	// read image 
	/*��2��������������ʽ��
Mat imread( const string& filename,int flags=1 );

��3������˵����
filename : ����ȡ��ͼ�������
flags �� ˵����ȡͼ�����������
���flags>0 , ��ô�ǰ�ͼ����س�3ͨ���Ĳ�ɫͼ��ע�⣺Ĭ�ϱ����س���һ����ɫͼ��
���flags=0,��ô��ͼ����سɻҶ�ͼ����ͨ����ͼ��
���flags<0,��ô���ͼ�����ǲ�ɫͼ���ͼ��سɲ�ɫͼ�����ͼ�����ǻҶ�ͼ�ͼ��سɻҶ�ͼ��
���ͼ�����ʧ�ܣ���ôimread�᷵��һ���վ���(Mat::data == NULL)��*/

	Mat img = imread(".\\imagefiles\\ali.jpg",1);
	if (img.empty()) {
		cerr << "can not load image." << endl;
	}

	// change pixel by atom "at"
	ChangeByAt(img);
	// change pixel by pointer	"ptr"
	ChangeByPtr(img);
	// ���opencv�� BGR��˳����� ����ڷŵ�˳��
	DisplayLocation(img);
	// ��� opencv �� Mat �ġ�ǳ������ �� �������
	DeepAndShadowCopy();

	system("pause");
	return 0;
}