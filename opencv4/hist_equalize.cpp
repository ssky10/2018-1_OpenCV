#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Hist_Equalize(Mat &gray_img);
void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200));

void hist_Equalize() {
	Mat gray_img = imread("./image/equalize_test.jpg", IMREAD_GRAYSCALE);
	imshow("srcImage", gray_img);
	Hist_Equalize(gray_img);
	imshow("dstImage", gray_img);
	waitKey(0);
	destroyAllWindows();
}

void Hist_Equalize(Mat &gray_img) {
	double sum[256], norm[256];
	int lut[256]; //Lookup Table

	//Initialize paramrters
	int histSize = 256; //bin size
	float range[] = { 0,256 };
	const float *ranges[] = { range };

	// 1) 히스토그램 계산
	Mat hist;
	calcHist(&gray_img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	// 2) 히스토그램 누적합 sum[i] 계산
	sum[0] = (double)hist.at<float>(0);
	for (int k = 1; k < 256; k++)
		sum[k] = sum[k - 1] + (double)hist.at<float>(k);

	// 3) 히스토그램 누적합 정규화 norm[i] 계산
	double totalPixelCounts = gray_img.rows * gray_img.cols;
	for (int k = 0; k < 256; k++)
		norm[k] = sum[k] / totalPixelCounts;

	// 4) 히스토그램 평활화를 위한 룩업 테이블 생성
	for (int k = 0; k < 256; k++)
		lut[k] = (int)(norm[k]*255);

	// 5) 룩업 테이블을 이용하여 평활화 수행
	int index, value;
	for (int r = 0; r < gray_img.rows; r++) {
		for (int c = 0; c < gray_img.cols; c++) {
			index = gray_img.at<uchar>(r, c);
			value = lut[index];
			gray_img.at<uchar>(r, c) = value;
		}
	}
}