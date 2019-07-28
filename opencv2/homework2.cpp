#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int homework2()
{
	Mat image = imread("./image/logo.jpg", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat null_image(image.size(), CV_8U, Scalar(0));

	Mat image_arr[3];
	split(image, image_arr);

	Mat ch0_arr[] = { image_arr[0], null_image, null_image };
	Mat ch0(image.size(), CV_8UC3);
	merge(ch0_arr, 3, ch0);

	Mat ch1_arr[] = { null_image, image_arr[1], null_image };
	Mat ch1(image.size(), CV_8UC3);
	merge(ch1_arr, 3, ch1);

	Mat ch2_arr[] = { null_image, null_image, image_arr[2] };
	Mat ch2(image.size(), CV_8UC3);
	merge(ch2_arr, 3, ch2);


	imshow("image", image);
	imshow("blue 채널", ch0);
	imshow("green 채널", ch1);
	imshow("red 채널", ch2);

	waitKey(0);
	return 0;
}