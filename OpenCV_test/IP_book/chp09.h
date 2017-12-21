#pragma once

using namespace cv;

// 测试各种形态学操作
void Morphology_Operate(void);
void Morp_Erode(void);// erode image and show result
void Morp_Dilate(void);// dilate image and show result
void Test_MorphologyEx(void); // test open, close, top hat, black hat
void Extract_edge(void);// use of morphologyEx
void Checken_0918(void); // chp0918 checken fig
void Move_Draft(void);// 去除水印draft

void Location_of_Anchor(void);// 测试 锚点的位置
void loc_anchor(void);// 

void Test_hit(void); // 测试击中变换

void Fig_text(void); //书中 P424，图9.29 text 处理


// 测试各种灰度图像的 形态学 操作
void Gray_Morphology(void);// 灰度图像的腐蚀，膨胀
void Fig_X_Ray(void);//  书中 P429 图 9.53 X 射线电子器件图
void Fig_Cloud(void);// 书中 P432，图9.38 cloud
void Fig_CT_bone(void);// 书中 P432，图9.39 CT bone
void Fig_Rice(void);// // 书中 P433，图9.40 rice 
void Fig_Nail(void);// // 书中 P434，图9.41 nail 
void test_Granulometry(void);// 测试理解的对不对
void Fig_Dots(void);// 书中 P435，图9.43 Dots 
void Fig_Calculator(void);//书中 P437，图9.44 Keybord 

void test_min(void);// 比较两个图片大小

// chp 09 课后作业 
void chp09_HomeWork(void);
void chp09_Q95(void); // 第九章 课后习题 问题 9.5