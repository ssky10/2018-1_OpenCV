#include <opencv2/opencv.hpp>
using namespace cv;

void myDCT(Mat srcImg, Mat& dstImg, int M, int N, int dir = 0);
Mat getDCT_filter_low(int N, int M);
Mat getDCT_filter_high(int N, int M);
Mat getDCT_filter_dc(int N, int M);
void DCT_filtering(Mat img, Mat filter, Mat& dst, int N, int M);

void main_DCT_opencv() {
	Mat image = imread("./image/lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);
	Mat filter = getDCT_filter_dc(8, 8);

	Mat floatImg,filter_img;
	image.convertTo(floatImg, CV_32F);
	Mat m_dct(floatImg.rows, floatImg.cols, CV_32FC1);
	Mat m_idct(floatImg.rows, floatImg.cols, CV_32FC1);
	myDCT(floatImg, m_dct, 8, 8);
	DCT_filtering(m_dct, filter, filter_img, 8, 8);
	myDCT(filter_img, m_idct, 8, 8,DCT_INVERSE);
	m_idct.convertTo(m_idct, CV_8U);

	imshow("image", image);
	imshow("idct", m_idct);
	waitKey(0);
}

void myDCT(Mat srcImg, Mat& dstImg, int M, int N, int dir) {
	if (M == 1 && N == 1)
		dct(srcImg, dstImg, dir);
	else {
		for (int bi = 0; bi < srcImg.rows; bi += M) {
			for (int bj = 0; bj < srcImg.cols; bj += N) {
				Rect rect = Rect(Point(bj, bi), Size(N, M));	
				Mat block = srcImg(rect), new_block;
				dct(block, new_block, dir);
				new_block.copyTo(dstImg(rect));
			}
		}
	}
}

Mat getDCT_filter_low(int N, int M) {
	Mat filter(N, M, CV_32F, Scalar(0));
	for (int i = 0; i < N / 4; i++)
		for (int j = 0; j < M / 4; j++)
			filter.at<float>(i, j) = 1;
	return filter;
}

Mat getDCT_filter_high(int N, int M) {
	Mat filter(N, M, CV_32F, Scalar(1));
	for (int i = 0; i < N / 4; i++)
		for (int j = 0; j < M / 4; j++)
			filter.at<float>(i, j) = 0;
	return filter;
}

Mat getDCT_filter_dc(int N, int M) {
	Mat filter(N, M, CV_32F, Scalar(0));
	for (int i = 0; i < N / 8; i++) //filter.at<float>(i, 0) = 1;
		for (int j = 0; j < M / 1; j++)
			filter.at<float>(i, j) = 1;
	return filter;
}

void DCT_filtering(Mat img, Mat filter, Mat& dst, int N, int M) {
	dst = Mat(img.size(), CV_32F);

	for (int bi = 0; bi < img.rows; bi += N) {
		for (int bj = 0; bj < img.cols; bj += M) {
			Rect rect = Rect(Point(bj, bi), Size(N, M));
			Mat new_block = img(rect);
			multiply(new_block, filter, new_block);
			new_block.copyTo(dst(rect));
		}
	}
}