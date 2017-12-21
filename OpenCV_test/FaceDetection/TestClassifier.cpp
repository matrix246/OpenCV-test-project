#include "stdafx.h"
#include "MyHeader1.h"

using namespace std;
using namespace cv;


void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale)
{
	int i = 0;
	double t = 0;
	vector<Rect> faces;
	const static Scalar colors[] = { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255) };//�ò�ͬ����ɫ��ʾ��ͬ������

	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);
	//��ͼƬ��С���ӿ����ٶ�

	cvtColor(img, gray, CV_BGR2GRAY);
	//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist(smallImg, smallImg);//ֱ��ͼ����

	t = (double)cvGetTickCount();//���������㷨ִ��ʱ��

								 //�������
								 //detectMultiScale������smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg��faces��ʾ��⵽������Ŀ�����У�1.1��ʾ
								 //ÿ��ͼ��ߴ��С�ı���Ϊ1.1��2��ʾÿһ����ѡ������Ҫ��¼2���ھ�,CV_HAAR_SCALE_IMAGE��ʾʹ��haar������Size(30, 30)
								 //ΪĿ�����С���ߴ�
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		| CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));

	t = (double)cvGetTickCount() - t;//���Ϊ�㷨ִ�е�ʱ��
	printf("detection time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//��ԭ��ԭ���Ĵ�С
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle(img, center, radius, color, 3, 8, 0);
		smallImgROI = smallImg(*r);
	}
	imshow("result", img);
}

int ShowDetectResult(Mat image, String cascadeName) {
	if (image.empty()) {
		cerr << "can not read image." << endl;
		system("pause");
	}

	CascadeClassifier cascade, nestedCascade;//������������������
	if (!cascade.load(cascadeName))//��ָ�����ļ�Ŀ¼�м��ؼ���������
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		system("pause");
		return 0;
	}

	double scale = 1.3;
	namedWindow("result", 1);//opencv2.0�Ժ���namedWindow�������Զ����ٴ���
	if (!image.empty())//��ȡͼƬ���ݲ���Ϊ��
	{
		detectAndDraw(image, cascade, scale);
		waitKey(0);
	}

	return 0;
}
