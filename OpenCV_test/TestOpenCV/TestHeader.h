#pragma once

using namespace cv;

// 测试 imread 函数，以及用两种方法改变像素的值。
// ref: http://blog.csdn.net/ebowtang/article/details/41811135
int imreadAndChangePixel(void);
void ChangeByAt(const Mat& img);
void ChangeByPtr(const Mat& img);
int DisplayLocation(const Mat& img); /* 理解并展示opencv中图像像素的位置 */
void DeepAndShadowCopy(void);  // 理解 opencv 中 Mat 的“浅拷贝” 与 “深拷贝”


int LoadVideo(void); /*test load video*/

// 测试几个常用滤波 以及 利用 filter2D 函数进行滤波
int TestFilterFuns(void);
void DifferentFilters(const Mat& img); /*test different kinds of filters*/
int UseFilter2D(const Mat& src, Mat& dst);/* 自己设计滤波核进行滤波 */


/* 构造 Mat 并查看 Mat 中分量相关的几个函数
ref: http://blog.csdn.net/qianqing13579/article/details/45318279
*/
int UseageOfMat(void);
int ConstructMat(void);
void InitialMat(void); // Mat 初始化
int ShowDetailsOfMat(const Mat& src);


/* 对图像进行改变，例如，合并，去除阴影等 */
int ChangeImage(void);
void TestCanny(const Mat& img);// 测试 canny 函数
void TestConverTo(const Mat& src);
void MyConcerTo(const Mat& src, Mat& dst, double alpha, double beta);
// 测试 converTo 成员函数，自己写一个调整对比度与亮度的函数
// ref: http://blog.csdn.net/chenjiazhou12/article/details/21119031
