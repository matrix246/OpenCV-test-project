#pragma once

using namespace cv;

/* get files from folder */
int GetFilesFromFolder(void);

/* check how to make folder */
int CheckAndMakeFolder(void);

/* Change image size */
int ResizeImage(void);

/* change all the image size and
sotre them into a new folder */
int ChangeImageSize(String SourceFolder, String TargetFolder, 
	int img_wid, int img_hei);

/* test the trained classifier */
void detectAndDraw(Mat& img, CascadeClassifier& cascade, double scale);

/*  show the detection result of an image */
int ShowDetectResult(Mat image, String cascadeName);