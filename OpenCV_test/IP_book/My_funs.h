#pragma once

using namespace cv;

void Show_Four_subimage(const Mat& img1,const Mat& img2,const Mat& img3,const Mat& img4,String str);// ��һ��ͼ��չʾ4����ͼ
void Print_Mat(const Mat& m);// ���MatԪ�أ������ǵ�ֵ��
// �Լ�����һ��  �ؽ�������  ����
void My_Reconstruct_Open(const Mat& src,Mat& dst,Mat& ker, int n);
