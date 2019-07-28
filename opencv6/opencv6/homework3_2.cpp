// �������󿡼��� ������ ó��
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void homework3_2()
{
	Mat gray_img = imread("./test_car/00.jpg", IMREAD_GRAYSCALE);
	Mat bin_img(gray_img.rows, gray_img.cols, CV_8UC1);
	threshold(gray_img, bin_img, 128, 255, THRESH_BINARY);
	namedWindow("��������", CV_WINDOW_AUTOSIZE);
	imshow("��������", bin_img);

	Mat ero_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat dil_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat edge_img(bin_img.rows, bin_img.cols, CV_8UC1);
	Mat mask = (Mat_<uchar>(3, 3) <<		// mask
		255, 255, 255,
		255, 255, 255,
		255, 255, 255);

	erode(bin_img, ero_img, mask);
	imshow("ħ�Ŀ���", ero_img);

	dilate(bin_img, dil_img, mask);
	imshow("��â����", dil_img);

	edge_img = dil_img - ero_img;
	imshow("��������", edge_img);

	waitKey(0);
	destroyAllWindows();
}

