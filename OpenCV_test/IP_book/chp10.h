#pragma once

using namespace cv;

// pixel based 测试点 线 的检测
void Line_Point_dection(void);

void Detect_Point_Fig_1004(void); // detect point in a plane
void Fig_1005(void);// remove line
void Angle_line_Fig_1007(void);// show line with angle

void Gradient_fig_116(void);// test gradient 
void Marr_Hildreth(void); // test marr Hildreth method

void test_houghLines(void);// test hough lines
void test_histogram(void);// test histogram

void test_threshold_fig_1038(void);// test threshold function
// adaptive threshold see the book in P478
void Adaptive_threshold(Mat& img,Mat& dst,double delate_thres);

void test_otsu(void);// test otsu function
void Fig_1041(void);// preprocessing before otsu
void Fig_1042(void);// preprocessing using laplacian before otsu

double otsu_8u_with_mask(const Mat src, const Mat mask);// otsu with mask
// 只对 mask 中非零位置的 src 中的像素计算直方图，进行otsu
void show_hist(int* h,int len);// display histogram failed 


void test_adaptiveThreshold(void);// test adaptive threshold 
void test_moving_threshold(void);//  test moving threshold fig 1049
void moving_threshold(const Mat& src,Mat& dst, double b, int n); // design moving threshold


