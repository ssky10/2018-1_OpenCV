// 이진영상에서의 형태학 처리
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void homework2_2()
{
	Mat gray_img = imread("./test_car/00.jpg", IMREAD_GRAYSCALE);

	imshow("명도영상", gray_img);

	Mat dst_img(gray_img.rows, gray_img.cols, CV_8UC1);
	Mat mask = (Mat_<uchar>(3, 3) <<		// mask
		255, 255, 255,
		255, 255, 255,
		255, 255, 255);

	erode(gray_img, dst_img, mask);
	imshow("침식영상", dst_img);

	dilate(gray_img, dst_img, mask);
	imshow("팽창영상", dst_img);

	morphologyEx(gray_img, dst_img, MORPH_OPEN, mask);
	imshow("열림영상", dst_img);

	morphologyEx(gray_img, dst_img, MORPH_CLOSE, mask);
	imshow("닫힘영상", dst_img);

	waitKey(0);
	destroyAllWindows();
}

