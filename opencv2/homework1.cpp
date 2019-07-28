#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void put_rect(Mat &frame, string text, Rect pt)
{
	rectangle(frame, pt, Scalar(0, 0, 255), 3);
}

int homework1()
{
	VideoCapture capture;
	capture.open("./image/video_file_in_text.avi");
	CV_Assert(capture.isOpened());

	double frame_rate = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / frame_rate;
	Mat  frame, roi;
	Rect roi1(200, 100, 100, 200);
	
	while (capture.read(frame))
	{
		roi = frame(roi1);
		roi += Scalar(0, 50, 0);

		if (waitKey(delay) >= 0) break;

		put_rect(frame, "frmae_cnt ", roi1 );
		imshow("동영상 파일읽기", frame);
	}
	return 0;
}