#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int edge_laplacian() {
	Mat image = imread("./image/laplacian_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	short data1[] = {
		0,1,0,
		1,-4,1,
		0,1,0
	};

	short data2[] = {
		-1,-1,-1,
		-1,8,-1,
		-1,-1,-1
	};

	Mat dst1, dst2;
	Mat mask1(3, 3, CV_16S, data1);
	Mat mask2(3, 3, CV_16S, data2);

	filter2D(image, dst1, CV_16S, mask1);
	filter2D(image, dst2, CV_16S, mask2);

	convertScaleAbs(dst1, dst1);
	convertScaleAbs(dst2, dst2);

	imshow("image", image);
	imshow("data1 filtering", dst1);
	imshow("data2 filtering", dst2);
	waitKey();
	return 0;
}
