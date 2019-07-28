#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int bin_at(Mat image, int value);
int bin_ptr(Mat image, int value);
void move_track(int value, void *userdata);

int mode=0;

int bin_image() {
	Mat image = imread("./image/image2.jpg", IMREAD_GRAYSCALE);
	int value=122;

	namedWindow("번호판");
	createTrackbar("mode", "번호판", &mode, 1);
	createTrackbar("기준값", "번호판", &value, 255, move_track, &image);

	bin_at(image, value);
	waitKey(0);
	return 0;
}

void move_track(int value, void *userdata) {
	// 시간 체크
	double t1, t2, time;
	t1 = static_cast<double>(getTickCount());

	if (mode == 0)
		bin_at((*(Mat*)userdata), value);
	else
		bin_ptr((*(Mat*)userdata), value);

	t2 = static_cast<double>(getTickCount());
	time = (t2 - t1) / getTickFrequency();
	printf("time = %f \n", time);
}

int bin_at(Mat image,int value) {
	Mat dst(image.size(), image.type());

	for (int i = 0, k = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++, k++) {
			dst.at<uchar>(i, j) = (image.at<uchar>(i, j) < value) ? 0 : 255;
		}
	}
	imshow("번호판", dst);
	return 0;
}

int bin_ptr(Mat image, int value) {
	Mat dst(image.size(), image.type());

	for (int i = 0, k = 0; i < image.rows; i++) {
		uchar * ptr_m1 = image.ptr<uchar>(i);
		uchar * ptr_m2 = dst.ptr<uchar>(i);
		for (int j = 0; j < image.cols; j++) {
			*(ptr_m2 + j) = (*(ptr_m1 + j) < value) ? 0 : 255;
		}
	}
	imshow("번호판", dst);
	return 0;
}
