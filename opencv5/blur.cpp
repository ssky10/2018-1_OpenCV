#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int blur_filtering() {
	Mat image = imread("./image/540x960-mobile-wallpapers-hd-2218x5ox3.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	float data1[] = {
		1 / 9.f,1 / 9.f,1 / 9.f,
		1 / 9.f,1 / 9.f,1 / 9.f,
		1 / 9.f,1 / 9.f,1 / 9.f
	};

	float data2[] = {
		1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,
		1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,
		1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,
		1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,
		1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f,1 / 25.f
	};

	Mat dst1, dst2, dst;
	Mat mask1(3, 3, CV_32F, data1);
	Mat mask2(5, 5, CV_32F, data2);

	filter2D(image, dst1, CV_32F, mask1);
	filter2D(image, dst2, CV_32F, mask2);
	dst1.convertTo(dst1, CV_8U);
	dst2.convertTo(dst2, CV_8U);

	imshow("image", image);
	imshow("data1 filtering", dst1);
	imshow("data2 filtering", dst2);
	waitKey();
	return 0;
}
