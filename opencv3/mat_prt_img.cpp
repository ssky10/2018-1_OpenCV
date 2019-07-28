#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int mat_ptr_img() {
	int value;
	cout << "값을 입력하세요:";
	cin >> value;

	Mat image = imread("./image/image.jpg", IMREAD_GRAYSCALE);
	Mat dst(image.size(), image.type());

	for (int i = 0, k = 0; i < image.rows; i++) {
		uchar * ptr_m1 = image.ptr<uchar>(i);
		uchar * ptr_m2 = dst.ptr<uchar>(i);
		for (int j = 0; j < image.cols; j++) {
			*(ptr_m2 + j) = (uchar)min(255,max(0, *(ptr_m1 + j) + value));
		}
	}
	imshow("원영상", image);
	imshow("조정영상", dst);
	waitKey(0);
	return 0;
}
