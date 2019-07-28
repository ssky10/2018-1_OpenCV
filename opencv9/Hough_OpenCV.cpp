#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Display_Lines(Mat &src_img, vector<Vec2f> lines);

void main_Hough_OpenCV() {
	int no;
	cout << "차량 영상 번호 :";
	cin >> no;

	string fname = format("./image/test_car/%02d.jpg", no);
	Mat src_img = imread(fname);
	imshow("원본 영상", src_img);

	Mat gray_img, edge_img;
	cvtColor(src_img, gray_img, CV_BGR2GRAY);
	GaussianBlur(gray_img, gray_img, Size(21, 5), 3, 1);
	Canny(gray_img, edge_img, 400, 100);
	imshow("Canny 에지 영상", edge_img);

	vector<Vec2f> lines;
	double rho = 1.5, theta = CV_PI / 180, threshold = 150;
	HoughLines(edge_img, lines, rho, theta, threshold);

	Display_Lines(src_img, lines);
	waitKey(0);
	destroyAllWindows();
}

void Display_Lines(Mat &src_img, vector<Vec2f> lines) {
	for (int i = 0; i < lines.size(); i++) {
		float rho = lines[i][0];
		float theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(src_img, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
	}
	imshow("Hough 직선 검출 영상", src_img);
}