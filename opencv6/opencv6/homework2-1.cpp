// �������󿡼��� ������ ó��
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void homework2_1()
{
	Mat gray_img = imread("./test_car/00.jpg", IMREAD_GRAYSCALE);

	imshow("������", gray_img);

	Mat dst_img(gray_img.rows, gray_img.cols, CV_8UC1);
	Mat mask = (Mat_<uchar>(5, 5) <<		// mask
		0, 0, 255, 0, 0,
		0, 255, 255, 255, 0,
		255, 255, 255, 255, 255,
		0, 255, 255, 255, 0,
		0, 0, 255, 0, 0);

	erode(gray_img, dst_img, mask);
	imshow("ħ�Ŀ���", dst_img);

	dilate(gray_img, dst_img, mask);
	imshow("��â����", dst_img);

	morphologyEx(gray_img, dst_img, MORPH_OPEN, mask);
	imshow("��������", dst_img);

	morphologyEx(gray_img, dst_img, MORPH_CLOSE, mask);
	imshow("��������", dst_img);

	waitKey(0);
	destroyAllWindows();
}

