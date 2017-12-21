#include "stdafx.h"
#include "IPbook.h"
#include "My_funs.h"
#include "chp09.h"
#include "chp10.h"

using namespace std;

void Detect_Point_Fig_1004(void){
	Mat img = imread(".//chp10//Fig1004(b)(turbine_blade_black_dot).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat dst;
	Mat ker = (Mat_<double>(3,3)<<1,1,1,1,-8,1,1,1,1);
	filter2D(img,dst,-1,ker);
	imshow("after filter" , dst);

	double thres = 250;
	double maxval = 255;
	threshold(dst,dst,thres,maxval,THRESH_BINARY);

	imshow("after threshold", dst);


} // detect point in a plane

void Fig_1005(void){
	Mat img = imread(".//chp10//Fig1005(a)(wirebond_mask).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat dst;
	Mat ker = (Mat_<double>(3,3)<<1,1,1,1,-8,1,1,1,1);
	filter2D(img,dst,-1,ker);
	imshow("after filter" , dst);

	threshold(dst,dst,0,255,THRESH_BINARY);
	imshow("bigger than 0", dst);
}
void Angle_line_Fig_1007(void){
	Mat img = imread(".//chp10//Fig1007(a)(wirebond_mask).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat dst;
	Mat ker = (Mat_<double>(3,3)<<2,-1,-1,-1,2,-1,-1,-1,2);
	filter2D(img,dst,-1,ker);
	imshow("after filter" , dst);
}


void Gradient_fig_116(void){
	Mat img = imread(".//chp10//Fig1016(a)(building_original).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat candst;
	Canny(img,candst,200,400);
	imshow("by canny",candst);

	// filter img by boxfilter
	boxFilter(img,img,-1,Size(5,5));

	Mat kerx,kery;

	kerx = (Mat_<double>(3,3)<<-1,-2,-1,0,0,0,1,2,1);
	kery = (Mat_<double>(3,3)<<-1,0,1,-2,0,2,-1,0,1);

	kerx = (Mat_<double>(3,3)<<0,1,1,-1,0,1,-1,-1,0);
	kery = (Mat_<double>(3,3)<<-1,-1,0,-1,0,1,0,1,1);

	kerx = (Mat_<double>(3,3)<<0,1,2,-1,0,1,-2,-1,0);
	kery = (Mat_<double>(3,3)<<-2,-2,0,-1,0,1,0,1,2);



	Mat gx;
	filter2D(img,gx,-1,kerx);
	imshow("|gx|" , gx);


	Mat gy;
	filter2D(img,gy,-1,kery);
	imshow("|gy|" , gy);

	Mat grad;
	grad = gx + gy;
	imshow("grad",grad);

	double minval,maxval;
	minMaxLoc(grad,&minval,&maxval);

	double thres = 0.33*maxval;
	threshold(grad,grad,thres,255,THRESH_BINARY);
	imshow("after threshold", grad);

}
void Marr_Hildreth(void){
	Mat img = imread(".//chp10//Fig1016(a)(building_original).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	// step 1 gaussian blur
	int n = 25;
	int sigx = 4;
	int sigy = 4;
	GaussianBlur(img,img,Size(n,n),sigx,sigy);

	// step 2 laplace 
	Laplacian(img,img,-1,3);
	imshow("step 1 and 2",img);

	// step 3 find zero cross

}


void test_houghLines(void){
	Mat img = imread(".//chp10//Fig1034(a)(marion_airport).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	// step 1 canny edge detection 
	double thres1 = 170;
	double thres2 = 340;
	Mat canimg;
	Canny(img,canimg,thres1,thres2);
	imshow("after canny",canimg);

	Mat dst;
	cvtColor(canimg,dst,CV_GRAY2BGR);

	// step 2 hough line detection
	double r = 1;
	double t = CV_PI/180;
	int thres = 220;
	// notice here, we use Mat to store the lines
	Mat lines;
	HoughLines(canimg,lines,r,t,thres);

	// note here the obtained points in associate with the Mat
	Vec2f tt = lines.at<Vec2f>(0,0);
	cout <<tt[0]<<tt[1];

	//// Draw the lines
	for( int i = 0; i < lines.cols; i++ )
	{
		Vec2f temp = lines.at<Vec2f>(0,i);
		float rho = temp[0], theta = temp[1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( dst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	}

	// Problem!!! we did not find the run way !!!
	imshow("img with lines", dst);

}
void test_histogram(void){
	//ref https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/histogram_calculation/histogram_calculation.html
	Mat img = imread(".//chp10//Fig1034(a)(marion_airport).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	/// Separate the image in 3 places ( B, G and R )
	Mat bgr_planes[3];
	split( img, bgr_planes );

	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	/// Compute the histograms:
	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
			Scalar( 255, 0, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
			Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
			Scalar( 0, 0, 255), 2, 8, 0  );
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
	imshow("calcHist Demo", histImage );

}


void Adaptive_threshold(Mat& img,Mat& dst,double delate_thres){
	Mat G1,G2,Mask1,Mask2;



	Scalar iniT = mean(img);
	double Ti,Ti_1;
	Ti = iniT[0];
	Ti_1 = 29999;

	Scalar M1,M2;
	double m1,m2;

	while(abs(Ti_1 - Ti) > delate_thres){
		Ti_1 = Ti;

		threshold(img,G1,Ti,255,THRESH_TOZERO);
		threshold(img,Mask1,Ti,1,THRESH_BINARY);
		cvtColor(Mask1,Mask1,CV_BGR2GRAY,1);
		threshold(img,G2,Ti,255,THRESH_TOZERO_INV);
		threshold(img,Mask2,Ti,1,THRESH_BINARY_INV);
		cvtColor(Mask2,Mask2,CV_BGR2GRAY,1);

		M1 = mean(G1,Mask1);
		M2 = mean(G2,Mask2);
		m1 = M1[0];
		m2 = M2[0];

		Ti = (m1 + m2)/2;
		cout << Ti<<endl;
	}

	threshold(img,dst,Ti,255,THRESH_BINARY);
	imshow("after threshold",dst);

}
void test_threshold_fig_1038(void){
	Mat img = imread(".//chp10//Fig1038(a)(noisy_fingerprint).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);
	Scalar m = mean(img);
	cout <<m[0]<<endl;

	Mat dst;
	Adaptive_threshold(img,dst,0);
	imshow("dst",dst);
}


void test_otsu(void){
	Mat img = imread(".//chp10//Fig1039(a)(polymersomes).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat adap_dst;
	Adaptive_threshold(img,adap_dst,0);

	Mat otsu_dst;
	// opencv 2.4.13中的threshold otsu 只能处理 8-bit 的图像，
	// 所以这里先将图像转换一下
	cvtColor(img,img,CV_BGR2GRAY,1);
	threshold(img,otsu_dst,100,255,THRESH_OTSU);
	imshow("otsu",otsu_dst);

}

void Fig_1041(void){
	Mat img = imread(".//chp10//Fig1041(a)(septagon_small_noisy_mean_0_stdv_10).tif");

	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat dst;
	boxFilter(img,dst,-1,Size(5,5));
	imshow("after mean filter",dst);

	cvtColor(img,img,CV_BGR2GRAY,1);
	threshold(img,img,2,255,THRESH_OTSU);
	imshow("using otsu before mean filter",img);

	cvtColor(dst,dst,CV_BGR2GRAY,1);
	threshold(dst,dst,2,255,THRESH_OTSU);
	imshow("using otsu after mean filter",dst);

}

double otsu_8u_with_mask(const Mat src, const Mat mask)
{
	const int N = 256;
	int M = 0; // M is for total number of none zero mask values
	// h[N] is for histogram
	int i, j, h[N] = { 0 };
	for (i = 0; i < src.rows; i++)
	{
		const uchar* psrc = src.ptr(i);
		const uchar* pmask = mask.ptr(i);
		for (j = 0; j < src.cols; j++)
		{
			if (pmask[j])
			{
				h[psrc[j]]++;
				++M;
			}
		}
	}

	// display histogram
	show_hist(h,N);

	double mu = 0, scale = 1. / (M);
	for (i = 0; i < N; i++)
		mu += i*(double)h[i];

	mu *= scale;
	double mu1 = 0, q1 = 0;
	double max_sigma = 0, max_val = 0;

	for (i = 0; i < N; i++)
	{
		double p_i, q2, mu2, sigma;

		p_i = h[i] * scale;
		mu1 *= q1;
		q1 += p_i;
		q2 = 1. - q1;

		// 若出现下面的情况，则不执行 if 后面的部分，继续执行 if 上面的部分
		if (std::min(q1, q2) < FLT_EPSILON || std::max(q1, q2) > 1. - FLT_EPSILON)
			continue;

		mu1 = (mu1 + i*p_i) / q1;
		mu2 = (mu - q1*mu1) / q2;
		sigma = q1*q2*(mu1 - mu2)*(mu1 - mu2);
		if (sigma > max_sigma)
		{
			max_sigma = sigma;
			max_val = i;
		}
	}
	return max_val;
}
void show_hist(int* h,int len){

	int maxval = 0;
	for (int i = 0;i <len ; i++)
	{
		if (maxval <= h[i])
			maxval = h[i];
	}

	Mat hist_img = Mat::zeros(maxval+1,len,CV_8U);
	for (int x = 0; x<len; x++)
	{
		hist_img.at<uchar>(Point(x,maxval - h[x])) = 255;
	}
	imshow("hist",hist_img);

	cout <<maxval<<endl;
}
void Fig_1042(void){
	Mat img = imread(".//chp10//Fig1042(a)(septagon_small_noisy_mean_0_stdv_10).tif");
	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);
	Mat img0 = img.clone();

	Mat maskimg;
	Laplacian(img,maskimg,-1,3);
	imshow("after laplacian",maskimg);

	double minval,maxval;
	minMaxLoc(maskimg,&minval,&maxval);

	threshold(maskimg,maskimg,maxval*0.997,255,THRESH_BINARY);
	imshow("maskimg",maskimg);	

	cvtColor(img0,img0,CV_BGR2GRAY,1);
	cvtColor(maskimg,maskimg,CV_BGR2GRAY,1);
	double thres_otsu = otsu_8u_with_mask(img0,maskimg);

	cout << "thres_otsu "<<thres_otsu<<endl;


	Mat dst;
	threshold(img0,dst,thres_otsu,255,THRESH_BINARY);
	imshow("after using otsu",dst);

	// 导出otsu 的阈值
}

void test_adaptiveThreshold(void){
	Mat img = imread(".//chp10//Fig1048(a)(yeast_USC).tif");

	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	Mat dst;
	cvtColor(img,img,CV_BGR2GRAY,1);
	double maxvlu = 255;
	adaptiveThreshold(img,dst,maxvlu,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,3,1);
	imshow("after adaptive threshold",dst);
}
void moving_threshold(const Mat& src,Mat& dst, double b, int n){

	double N = src.rows * src.cols;
	double maxval = 255;
	// reshape the original image to a single line
	Mat temp = src.reshape(0,1);
	Mat temp_dst = Mat::zeros(1,N,CV_8U);

	// 利用 书 P491 式（10.3-38）中的第二个表达式
	double m_k;
	m_k = temp.at<uchar>(0)/n;
	for (int i = 0; i < n; i++)
	{
		if (temp.at<uchar>(i) > b * m_k)
			temp_dst.at<uchar > (i) = maxval;
	}


	for (int i = n; i < N; i++)
	{
		m_k = m_k + (temp.at<uchar>(i) - temp.at<uchar>(i-n))/n;
		if (temp.at<uchar>(i) > b * m_k)
			temp_dst.at<uchar > (i) = maxval;
	}

	dst = temp_dst.reshape(0,src.rows);
}
void test_moving_threshold(void){
	//Mat img = imread(".//chp10//Fig1049(a)(spot_shaded_text_image).tif");
	Mat img = imread(".//chp10//Fig1050(a)(sine_shaded_text_image).tif");

	if (img.empty())
	{
		cerr<<"can not read image"<<endl;
	}
	imshow("original image", img);

	// // 利用adaptiveThreshold 也可以得到比较好的结果
	//Mat dst;
	//cvtColor(img,img,CV_BGR2GRAY,1);
	//double maxvlu = 255;
	//adaptiveThreshold(img,dst,maxvlu,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,3,2);
	//imshow("after moving threshold",dst);

	// 但是利用 moving threshold 得到的 结果更好一些，特别是对于那个有竖状条纹的图 10 50
	Mat dst;
	cvtColor(img,img,CV_BGR2GRAY,1);
	moving_threshold(img,dst,0.5,300);
	imshow("dst ",dst);
}


void Line_Point_dection(){
	//Detect_Point_Fig_1004();

	//Fig_1005();
	//Angle_line_Fig_1007();

	//Gradient_fig_116();// test gradient 
	//Marr_Hildreth();
	//test_houghLines();
	//test_histogram();

	//test_threshold_fig_1038();

	//test_otsu();
	//Fig_1041();
	//Fig_1042();

	//test_adaptiveThreshold();
	test_moving_threshold();


	//waitKey();
}