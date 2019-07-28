#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int edge_sobel() {
	Mat image = imread("./image/edge_test1.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	short data1[] = {
		-1,-2,-1,
		0,0,0,
		1,2,1
	};

	short data2[] = {
		-1,0,1,
		-2,0,2,
		-1,0,1
	};

	Mat dst1, dst2, dst;
	Mat mask1(3, 3, CV_16S, data1);
	Mat mask2(3, 3, CV_16S, data2);

	filter2D(image, dst1, CV_32F, mask1);
	filter2D(image, dst2, CV_32F, mask2);
	magnitude(dst1, dst2, dst);
	dst.convertTo(dst, CV_8U);

	imshow("image", image);
	imshow("data1 filtering", dst1);
	imshow("data2 filtering", dst2);
	imshow("Sobel filtering", dst);
	waitKey();
	return 0;
}
