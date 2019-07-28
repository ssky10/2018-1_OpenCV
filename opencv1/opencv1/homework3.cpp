#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int homework3()
{
	Mat image(600, 400, CV_8UC3);
	Rect rect(100,100,200,300);

	rectangle(image, rect, Scalar(0, 0, 255), FILLED, 0);

	imshow("°úÁ¦3", image);
	waitKey();
	destroyAllWindows();

	return 0;
}