#include "stdafx.h"
#include <io.h> // for _access();
#include <direct.h>  // for _mkdir();

using namespace std;
using namespace cv;

int ResizeImage() {

	int img_wid = 20;
	int img_hei = 20;

	Mat src = imread(".\\Resources\\neg_files\\1.png");
	if (src.empty()) {
		cout << "can not read image. " << endl;
	}

	Mat dst(img_wid, img_hei, src.type());
	resize(src, dst, dst.size());
	imwrite(".\\Resources\\1.jpg", dst);

	return 0;

}

int ChangeImageSize(String SourceFolder, String TargetFolder,
	int img_wid, int img_hei) {

	// check if the folder existed
	if (_access(SourceFolder.c_str(),0) == -1) {
		cout << "folder" << SourceFolder << " do not exist!" << endl;
		return -1;
	}

	// find all the images in the folder and subfolders
	vector<String> fn;
	glob(SourceFolder, fn, true);
	cout << "The number of image is: " << fn.size() << endl;

	// create a folder to store all the images
	int flag = _mkdir(TargetFolder.c_str());
	if (flag == 0) {
		cout << "successfully create a folder." << endl;
	}
	else {
		cout << "folder already existed." << endl;
	}

	// change the images into gray and
	// resize all these images and store them into new folder
	Mat src = imread(fn[0]);
	Mat GraySrc;
	cvtColor(src, GraySrc, CV_BGR2GRAY);
	if (src.empty()) {
		cout << "can not read image. " << endl;
	}
	Mat dst(img_wid, img_hei, GraySrc.type());


	//// check what is happen in 1704 
	//int j = 3324;
	//cout << fn[j] << endl;
	//src = imread(fn[j]);


	for (int i = 0; i < fn.size(); i++) {
		src = imread(fn[i]);
		cvtColor(src, GraySrc, CV_BGR2GRAY);
		resize(GraySrc, dst, dst.size());
		String imgName = TargetFolder + "\\" + to_string(i) + ".jpg";
		imwrite(imgName, dst);
		if (!dst.data)
			cerr << "can not load image" << endl;
	}

	return 0;

}