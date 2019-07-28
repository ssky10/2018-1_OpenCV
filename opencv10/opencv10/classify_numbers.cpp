#pragma once
#include "preprocess.hpp"					// 전처리 및 후보영역 검출 함수
#include "candiate.hpp"						// 후보영역 개선 및 후보영상 생성 함수
#include "SVM.hpp"						// 학습데이터 로드 및 SVM 수행
#include "kNN.hpp"						// kNN 학습 함수 – 10장 3절
#include "classify_objects.hpp"			// kNN 분류 함수

int find_carnumber()
{
	int K1 = 15;
	Ptr<ml::KNearest> knn[1];
	knn[0] = kNN_train("./image/train_texts.png", K1, 25, 20);

	// 	학습된 데이터 로드
	Ptr<ml::SVM> svm = ml::StatModel::load<ml::SVM>("./SVMtrain.xml");
	Ptr<ml::SVM> svm_number = ml::StatModel::load<ml::SVM>("./NUMBERtrain.xml");

	int car_no;
	cout << "차량 영상 번호 (0-20) : ";
	cin >> car_no;
	string fn = format("./image/test_car/%02d.jpg", car_no);
	Mat image = imread(fn, 1);
	Mat img_temp = image.clone();
	CV_Assert(image.data);

	Mat morph = preprocessing(image);								// 전처리
	vector<RotatedRect> candidates;
	find_candidates(morph, candidates);									// 후보 영역 검출
	for (int i = 0; i < candidates.size(); i++) {
		Point2f pts[4];
		RotatedRect temp = candidates[i];
		rectangle(img_temp, temp.boundingRect(), Scalar(255));
		temp.points(pts);
		for (int j = 0; j < 4; j++) {
			line(img_temp, pts[j], pts[(j + 1) % 4], Scalar(255));
		}
	}
	vector<Mat> candidate_img = make_candidates(image, candidates);// 후보 영상 생성

	int plate_no = classify_plates(svm , candidate_img);			// SVM 분류

	if (plate_no >= 0) 
	{
		vector <Rect> obejct_rects, sorted_rects;
		vector <Mat> numbers;							// 숫자 객체 
		Mat  plate_img, color_plate;								// 컬러 번호판 영상 

		preprocessing_plate(candidate_img[plate_no], plate_img);	// 번호판 영상 전처리
		cvtColor(plate_img, color_plate, CV_GRAY2BGR);

		find_objects(~plate_img, obejct_rects);		// 숫자 및 문자 검출  

		sort_rects(obejct_rects, sorted_rects);			// 검출객체 정렬(x 좌표기준)

		for (size_t i = 0; i < sorted_rects.size(); i++) 
		{
			numbers.push_back(plate_img(sorted_rects[i]));	// 정렬된 숫자 영상
			//imshow(format("%d번", i), numbers[i]);
			rectangle(color_plate, sorted_rects[i], Scalar(0, 0, 255), 1); // 사각형 그리기
		}

		if (numbers.size() == 7) {
			classify_numbers(numbers, svm_number, knn, K1);		// kNN 분류 수행
			cout << endl;
		}
		else  cout << "숫자(문자) 객체를 정확히 검출하지 못했습니다." << endl;

		imshow("번호판 영상", color_plate);					// 번호판 영상 표시
		draw_rotatedRect(image, candidates[plate_no], Scalar(0, 0, 255), 2);
	}
	else  cout << "번호판을 검출하지 못하였습니다. " << endl;

	imshow("image", img_temp);
	waitKey();
	destroyAllWindows();
	return 0;
}


void find_histoPos(Mat img, int & start, int &end, int direct)
{
	reduce(img, img, direct, REDUCE_AVG);

	int  minFound = 0;
	for (int i = 0; i< (int)img.total(); i++) {
		if (img.at<uchar>(i) < 250)
		{
			end = i;
			if (!minFound) {
				start = i;
				minFound = 1;
			}
		}
	}
}

Mat find_number(Mat part)
{
	Point start, end;
	find_histoPos(part, start.x, end.x, 0);
	find_histoPos(part, start.y, end.y, 1);

	return part(Rect(start, end));
}

Mat  place_middle(Mat number, Size new_size)
{
	int  big = max(number.cols, number.rows);
	Mat  square(big, big, number.type(), Scalar(255));

	Point start = (square.size() - number.size()) / 2;

	Rect middle_rect(start, number.size());
	Mat middle = square(middle_rect);
	number.copyTo(middle);

	resize(square, square, new_size);
	square.convertTo(square, CV_32F);

	return square.reshape(0, 1);
}
