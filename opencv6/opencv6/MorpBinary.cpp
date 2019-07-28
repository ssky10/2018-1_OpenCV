// 이진영상에서의 형태학 처리
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void ex_Morphology_Binary()
{
	Mat gray_img = imread("./test_car/00.jpg", IMREAD_GRAYSCALE);
	Mat bin_img(gray_img.rows, gray_img.cols, CV_8UC1);
	threshold(gray_img, bin_img, 128, 255, THRESH_BINARY);
	namedWindow( "이진영상", CV_WINDOW_AUTOSIZE );  
    imshow( "이진영상", bin_img);  

	Mat dst_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat mask = (Mat_<uchar>(3, 3) <<		// mask
				0,   0,   0,      
	            255, 255, 255,
	 	        0,   0,   0);
	
	erode(bin_img, dst_img, mask);
    imshow( "침식영상", dst_img);

	dilate(bin_img, dst_img, mask);
    imshow( "팽창영상", dst_img);

	morphologyEx(bin_img, dst_img, MORPH_OPEN, mask);
	imshow("열림영상", dst_img);

	morphologyEx(bin_img, dst_img, MORPH_CLOSE, mask);
	imshow("닫힘영상", dst_img);
	
	waitKey(0);
	destroyAllWindows();
}

