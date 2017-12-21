#pragma once

using namespace cv;

void Show_Four_subimage(const Mat& img1,const Mat& img2,const Mat& img3,const Mat& img4,String str);// 在一幅图中展示4个子图
void Print_Mat(const Mat& m);// 输出Mat元素，必须是单值的
// 自己构造一个  重建开操作  函数
void My_Reconstruct_Open(const Mat& src,Mat& dst,Mat& ker, int n);
