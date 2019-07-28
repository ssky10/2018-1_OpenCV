#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int homework2()
{
	Mat m(10, 15, CV_32S, Scalar(100)),m2;
	m2 = m(Rect(3, 1, 5, 4));
	m2.setTo(200);
	m2 = m(Rect(8, 5, 6, 4));
	m2.setTo(300);
	m2 = m(Rect(5, 3, 5, 4));
	m2.setTo(500);

	cout << m << endl << endl;
	return 0;
}