#include "stdafx.h"
#include <io.h> // for _access();
#include <direct.h>  // for _mkdir();
#include "MyHeader1.h"

using namespace std;
using namespace cv;

int PrepareImage(String FolderName , String TargetFolder) {


	// find all the images in the folder and subfolders
	vector<String> fn;
	glob(FolderName, fn, true);
	cout << "The number of image is: " << fn.size() << endl;

	// read and modify an image into gray 
	Mat image = imread(fn[3500]);
	Mat dst;
	cvtColor(image , dst , CV_BGR2GRAY);

	// 将所有图片转化为灰度图片



	//ChangeImageSize(String SourceFolder, String TargetFolder,
		//int img_wid, int img_hei);
	return 0;
}