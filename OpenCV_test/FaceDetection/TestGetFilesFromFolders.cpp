#include "stdafx.h"

#include <direct.h>  // for _mkdir();

using namespace std;
using namespace cv;

int CheckAndMakeFolder() {

	String Filename = ".\\Resources\\test_neg_image";
	int flag = _mkdir(Filename.c_str());
	if (flag == 0) {
		cout << "successfully create a folder." << endl;
	}
	else {
		cout << "folder already existed." << endl;
	}

	return 0;

}

int GetFilesFromFolder() {

	// find all the images in the folder and subfolders
	vector<String> fn;
	String path = ".\\Resources\\neg_files";
	glob(path, fn, true);
	cout << "The number of image is: " << fn.size() << endl;


	// create a folder to store all the images
	String FolderName = ".\\Resources\\test_neg_image";
	int flag = _mkdir(FolderName.c_str());
	if (flag == 0) {
		cout << "successfully create a folder." << endl;
	}
	else {
		cout << "folder already existed." << endl;
	}

	// write these images into the newly created folder
	for (int i = 0; i < fn.size(); i++) {
		Mat ImaTarget = imread(fn[i]);
		String imgName = FolderName + "\\" + to_string(i) + ".jpg";
		imwrite(imgName, ImaTarget);
		if (!ImaTarget.data)
			cerr << "can not load image" << endl;
	}
	

	return 0;
}

