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

	// 1) ������׷� ���
	Mat hist;
	calcHist(&gray_img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	// 2) ������׷� ������ sum[i] ���
	sum[0] = (double)hist.at<float>(0);
	for (int k = 1; k < 256; k++)
		sum[k] = sum[k - 1] + (double)hist.at<float>(k);

	// 3) ������׷� ������ ����ȭ norm[i] ���
	double totalPixelCounts = gray_img.rows * gray_img.cols;
	for (int k = 0; k < 256; k++)
		norm[k] = sum[k] / totalPixelCounts;

	// 4) ������׷� ��Ȱȭ�� ���� ��� ���̺� ����
	for (int k = 0; k < 256; k++)
		lut[k] = (int)(norm[k]*255);

	// 5) ��� ���̺��� �̿��Ͽ� ��Ȱȭ ����
	int index, value;
	for (int r = 0; r < gray_img.rows; r++) {
		for (int c = 0; c < gray_img.cols; c++) {
			index = gray_img.at<uchar>(r, c);
			value = lut[index];
			gray_img.at<uchar>(r, c) = value;
		}
	}
}