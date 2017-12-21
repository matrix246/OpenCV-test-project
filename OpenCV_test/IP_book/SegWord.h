#pragma once

using namespace cv;

// 文字分割的第一个版本，利用水平和竖直方向的投影直方图
// 只能处理横平竖直的文本
void Seg_word_1(void);

void Find_begin_end_len(Mat h_vec,Mat& locations,int& count, int width);
// find the begin end and len of words and store in locations

void test_pointer(int* a, int b, int& c);// test function with pointer
void use_test_pointer(void);// use test pointer function
void test_list(void);// 链表的使用


// 文字分割的第二个版本，利用腐蚀，寻找连通区域做
// 期望能处理更复杂的情形
void Seg_word_2(void);

void step_1_erode(Mat& img);// 先对图像进行腐蚀
void step_2_find_conection(const Mat& original_img, Mat& img_erode);// 找到连通区域

// 模板匹配
void rotate_keep_size(const Mat& img, Mat& dst, double degree, double scale);// 利用 warpAffine 旋转图像，保持所有内容

void Template_match_1(void);// 利用 matchTemplate  函数进行匹配
