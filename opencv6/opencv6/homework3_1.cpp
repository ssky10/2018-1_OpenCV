// 이진영상에서의 형태학 처리
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void homework3_1()
{
	Mat gray_img = imread("./test_car/00.jpg", IMREAD_GRAYSCALE);
	Mat bin_img(gray_img.rows, gray_img.cols, CV_8UC1);
	threshold(gray_img, bin_img, 128, 255, THRESH_BINARY);
	namedWindow("이진영상", CV_WINDOW_AUTOSIZE);
	imshow("이진영상", bin_img);

	Mat ero_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat dil_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat edge_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat mask = (Mat_<uchar>(5, 5) <<		// mask
		0, 0, 255, 0, 0,
		0, 255, 255, 255, 0,
		255, 255, 255, 255, 255,
		0, 255, 255, 255, 0,
		0, 0, 255, 0, 0);

	erode(bin_img, ero_img, mask);
	imshow("침식영상", ero_img);

	dilate(bin_img, dil_img, mask);
	imshow("팽창영상", dil_img);

	edge_img = dil_img - ero_img;
	imshow("엣지영상", edge_img);

	waitKey(0);
	destroyAllWindows();
}

