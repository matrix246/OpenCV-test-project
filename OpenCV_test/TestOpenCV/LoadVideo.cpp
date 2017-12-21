#include "stdafx.h"

using namespace std;
using namespace cv;

int LoadVideo(void) {

	// 1. read the video and show the video
	VideoCapture capture(".\\imagefiles\\video.mp4");
	// check if video successfully opened
	if (capture.isOpened())
		cout << "successsfully opened the video" << endl;
	else
	{
		cout << "can not open the video" << endl;
		return -1;
	}



	// show the video frame by frame
	Mat Single_frame;

	namedWindow("current frame", WINDOW_NORMAL); // to show the whole image
	while (1)
	{
		capture >> Single_frame;
		if (Single_frame.empty())  break;
		imshow("current frame", Single_frame);
		/*
		������һ�仰����˼�ǣ�
		���10ms֮��û�в������������һ��
		����в�����������ֹͣ
		*/
		if ( waitKey(10) < 0)  	break; // ÿһ֡��ˢ��ʱ����Ϊ10 ����
	}
	return 0;
}