#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int find_carnumber();
void train_number();

int main() {
	int select;
	cout << "�۾��� �������ּ���(1-��ȣ SVM ����/3-��ȣ�� ����):";
	cin >> select;
	switch (select)
	{
	case 1:
		train_number();
		break;
	case 2:
		while (1) {
			find_carnumber();
		}
		break;
	case 3:
		
		break;
	default:
		cout << "�߸��� �����Դϴ�." << endl;
		break;
	}
}
