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
		下面这一句话的意思是：
		如果10ms之内没有操作，则进行下一步
		如果有操作，则立即停止
		*/
		if ( waitKey(10) < 0)  	break; // 每一帧的刷新时间间隔为10 毫秒
	}
	return 0;
}