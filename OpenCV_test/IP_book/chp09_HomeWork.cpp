#include "stdafx.h"
#include "My_funs.h"
#include "IPbook.h"
#include "chp09.h"

using namespace std;

void chp09_Q95(){

	Mat img = imread(".\\chp09\\FigP0905(U).tif");
	if (img.empty())
	{
		cerr << "can not read image."<<endl;
	}

	imshow("U style",img);




}

void chp09_HomeWork(){

	chp09_Q95();

	waitKey();
}