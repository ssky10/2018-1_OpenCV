#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

String title4 = "과제4";
void onMouse2(int, int, int, int, void *);		// 마우스 콜백 함수
Mat imageMC(200, 300, CV_8U);

int homework4()
{
	imageMC.setTo(255);							// image 행렬 초기화 - 흰색 바탕
	imshow(title4, imageMC);

	setMouseCallback(title4, onMouse2, 0);
	waitKey(0);
	return 0;
}

void onMouse2(int event, int x, int y, int flags, void * param)
{
	switch (event)			//switch문으로 event값에 따라 버튼 종류를 구분
	{
	case EVENT_LBUTTONDOWN:	rectangle(imageMC, Rect(x,y,30,30), Scalar(0), 1);	break;
	case EVENT_RBUTTONDOWN:	circle(imageMC, Point(x,y), 20, Scalar(0), 1); break;
	}

	imshow(title4, imageMC);
}