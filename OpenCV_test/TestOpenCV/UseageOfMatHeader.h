#pragma once

/* ���� Mat ���鿴 Mat �з�����صļ������� 
ref: http://blog.csdn.net/qianqing13579/article/details/45318279
*/
int ConstructMat(void);

/* Mat �ĸ��ֲ��� */
int MethodsForMat(void);

/* �Լ�����˲��˽����˲� */
int SharpenUseFilter2D(const Mat& src, Mat&dst);

/* չʾ�˲���� */
int ShowFilteredResult(void);