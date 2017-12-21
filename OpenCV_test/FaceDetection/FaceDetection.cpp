// FaceDetection.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyHeader1.h"

using namespace cv;
int main()
{



	//CheckAndMakeFolder();

	//GetFilesFromFolder();

	//ResizeImage();

	// step 1
	// change all the image into gray and 
	// change size of the face image ioto 20*20
	
	//int dst_img_wid = 60;
	//int dst_img_hei = 60;
	//String SourceFolder = ".\\Resources\\neg_files";
	//String TargetFolder = ".\\Resources\\neg_image";
	//ChangeImageSize(SourceFolder,TargetFolder,
	//dst_img_wid, dst_img_hei);

	// step 2
	//prepare pos_image.txt and neg_image.txt
	/*
	open cmd window in the "pos_image" folder
	input: dir /s/b >pos_image.txt
	then modify the last several column in the file
    */

   // step 3
   // create the vec file
   /*
   copy  opencv_createsamples.exe and
   opencv_traincascade.exe from the folder of opencv32
   D:\Opencv32\build\x64\vc14\bin
   into the "Resources" folder

   open cmd window in the "Resources" folder
   input: opencv_createsamples.exe -vec pos.vec -info pos_image.txt -bg neg_image.txt -w 20 -h 20 -num 432

   or
   click"PreparePosSample.bat"

   ref:http://www.cnblogs.com/tornadomeet/archive/2012/03/28/2420936.html
   */

   // step 4
   // use opencv_traincascade.exe for training 
   /*
   create a folder "xml" to store the obtained xml files

   open cmd window in the "Resources" folder
   input: opencv_traincascade.exe -data xml -vec pos.vec -bg neg_image.txt -numPos 40 -numNeg 100 -numStages 8 -w 20 -h 20

   or
   click "TrainClassifier.bat"

   ref:http://blog.csdn.net/xidianzhimeng/article/details/10470839
   */


	// step 5
	// test the classifier

	String cascadeName = ".\\Resources\\xml\\cascade.xml";
	Mat image = imread(".\\Resources\\TestImages\\li.jpg");
	ShowDetectResult(image, cascadeName);

	system("pause");

	return 0;
}

