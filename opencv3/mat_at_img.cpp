#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int mat_at_img() {
	Mat image = imread("./image/image.jpg",IMREAD_GRAYSCALE);
	Mat dst(image.size(), image.type());

	for (int i = 0, k = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++, k++) {
			dst.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
		}
	}
	imshow("원영상", image);
	imshow("반전영상", dst);
	waitKey(0);
	return 0;
}
