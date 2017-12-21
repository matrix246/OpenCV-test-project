#pragma once

/* 构造 Mat 并查看 Mat 中分量相关的几个函数 
ref: http://blog.csdn.net/qianqing13579/article/details/45318279
*/
int ConstructMat(void);

/* Mat 的各种操作 */
int MethodsForMat(void);

/* 自己设计滤波核进行滤波 */
int SharpenUseFilter2D(const Mat& src, Mat&dst);

/* 展示滤波结果 */
int ShowFilteredResult(void);