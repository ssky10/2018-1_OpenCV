#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int bin_ptr(Mat image, Mat &dst, int value);

void threshold_number() {
	Mat gray_img = imread("./image/image.jpg", IMREAD_GRAYSCALE);
	Mat hist, dst_img(gray_img.size(), gray_img.type());

	int sum = 0, size = gray_img.rows * gray_img.cols;
	int level = 0;

	//Initialize paramrters
	int histSize = 256; //bin size
	float range[] = { 0,256 };
	const float *ranges[] = { range };

	// 1) 히스토그램 계산
	calcHist(&gray_img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
	
	imshow("srcImage", gray_img);
	for (int k = 0; k < 256; k++) {
		sum += (int)hist.at<float>(k);
		if (sum * 2 > size) {
			level = k;
			break;
		}
	}
	cout << level;
	bin_ptr(gray_img, dst_img, level);
	waitKey(0);
	destroyAllWindows();
}

int bin_ptr(Mat image, Mat &dst, int value) {
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
