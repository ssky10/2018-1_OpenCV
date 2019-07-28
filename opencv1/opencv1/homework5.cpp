#include <opencv2/opencv.hpp>
using namespace cv;

void onMouse3(int, int, int, int, void *);

String title5 = "����5";
int lineValue = 5;
int rValue = 25;
Mat imageMT(400, 600, CV_8U);

int homework5()
{
	imageMT.setTo(255);

	namedWindow(title5, WINDOW_AUTOSIZE);
	createTrackbar("������", title5, &lineValue, 10);
	createTrackbar("������ũ��", title5, &rValue, 50);

	imshow(title5, imageMT);

	setMouseCallback(title5, onMouse3, 0);

	waitKey(0);
	return 0;
}

void onMouse3(int event, int x, int y, int flags, void * param)
{
	switch (event)			//switch������ event���� ���� ��ư ������ ����
	{
	case EVENT_LBUTTONDOWN:	rectangle(imageMT, Rect(x, y, 30, 30), Scalar(0), lineValue); break;
	case EVENT_RBUTTONDOWN:	circle(imageMT, Point(x, y), rValue, Scalar(0), lineValue); break;
	}

	imshow(title5, imageMT);
}