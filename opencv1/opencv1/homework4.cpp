#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

String title4 = "����4";
void onMouse2(int, int, int, int, void *);		// ���콺 �ݹ� �Լ�
Mat imageMC(200, 300, CV_8U);

int homework4()
{
	imageMC.setTo(255);							// image ��� �ʱ�ȭ - ��� ����
	imshow(title4, imageMC);

	setMouseCallback(title4, onMouse2, 0);
	waitKey(0);
	return 0;
}

void onMouse2(int event, int x, int y, int flags, void * param)
{
	switch (event)			//switch������ event���� ���� ��ư ������ ����
	{
	case EVENT_LBUTTONDOWN:	rectangle(imageMC, Rect(x,y,30,30), Scalar(0), 1);	break;
	case EVENT_RBUTTONDOWN:	circle(imageMC, Point(x,y), 20, Scalar(0), 1); break;
	}

	imshow(title4, imageMC);
}