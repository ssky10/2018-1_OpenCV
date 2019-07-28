#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void  calc_Histo(const Mat& image, Mat& hist, int bins, int range_max = 256);

void draw_histo(Mat hist, Mat &hist_img, Size size = Size(256, 200));

int draw_histogram()
{
	Mat image = imread("./image/pixel_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(!image.empty());

	Mat hist, hist_img;
	calc_Histo(image, hist, 256);
	draw_histo(hist, hist_img);

	imshow("hist_img", hist_img);
	imshow("image", image);
	waitKey();
	return 0;
}