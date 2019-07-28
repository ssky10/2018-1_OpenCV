#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int homework4_2() {
	while (1) {
		int no;
		cout << "���� ���� ��ȣ (0:����) :";
		cin >> no;
		if (no == 0) break;

		string fname = format("./test_car/%02d.jpg", no);
		Mat image = imread(fname, 1);
		if (image.empty()) {
			cout << to_string(no) + "�� ���� ������ �����ϴ�." << endl;
			continue;
		}

		Mat gray, sobel, th_img, morph;
		Mat kernel(10, 40, CV_8UC1, Scalar(1));
		cvtColor(image, gray, CV_BGR2GRAY);

		blur(gray, gray, Size(5, 5));
		Sobel(gray, gray, CV_8U, 1, 0, 3);

		threshold(gray, th_img, 120, 255, THRESH_BINARY);
		morphologyEx(th_img, morph, MORPH_CLOSE, kernel);

		imshow("image", image);
		imshow("��������", th_img);
		imshow("��������", morph);
		waitKey(0);
	}
	return 0;
}