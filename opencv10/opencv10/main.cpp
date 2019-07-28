#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int find_carnumber();
void train_number();

int main() {
	int select;
	cout << "작업을 선택해주세요(1-번호 SVM 생성/3-번호판 검출):";
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
		cout << "잘못된 선택입니다." << endl;
		break;
	}
}
