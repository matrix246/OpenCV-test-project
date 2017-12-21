#pragma once

using namespace cv;

// ���� imread �������Լ������ַ����ı����ص�ֵ��
// ref: http://blog.csdn.net/ebowtang/article/details/41811135
int imreadAndChangePixel(void);
void ChangeByAt(const Mat& img);
void ChangeByPtr(const Mat& img);
int DisplayLocation(const Mat& img); /* ��Ⲣչʾopencv��ͼ�����ص�λ�� */
void DeepAndShadowCopy(void);  // ��� opencv �� Mat �ġ�ǳ������ �� �������


int LoadVideo(void); /*test load video*/

// ���Լ��������˲� �Լ� ���� filter2D ���������˲�
int TestFilterFuns(void);
void DifferentFilters(const Mat& img); /*test different kinds of filters*/
int UseFilter2D(const Mat& src, Mat& dst);/* �Լ�����˲��˽����˲� */


/* ���� Mat ���鿴 Mat �з�����صļ�������
ref: http://blog.csdn.net/qianqing13579/article/details/45318279
*/
int UseageOfMat(void);
int ConstructMat(void);
void InitialMat(void); // Mat ��ʼ��
int ShowDetailsOfMat(const Mat& src);


/* ��ͼ����иı䣬���磬�ϲ���ȥ����Ӱ�� */
int ChangeImage(void);
void TestCanny(const Mat& img);// ���� canny ����
void TestConverTo(const Mat& src);
void MyConcerTo(const Mat& src, Mat& dst, double alpha, double beta);
// ���� converTo ��Ա�������Լ�дһ�������Աȶ������ȵĺ���
// ref: http://blog.csdn.net/chenjiazhou12/article/details/21119031
