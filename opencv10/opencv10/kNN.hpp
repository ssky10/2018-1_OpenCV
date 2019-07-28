#pragma once


void find_histoPos_knn(Mat img, int & start, int &end, int direct)
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

Mat find_number_knn(Mat part)
{
	Point start, end;
	find_histoPos_knn(part, start.x, end.x, 0);
	find_histoPos_knn(part, start.y, end.y, 1);

	return part(Rect(start, end));
}

Mat  place_middle_knn(Mat number, Size new_size)
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

Ptr<ml::KNearest>   kNN_train(string train_img, int K, int Nclass, int Nsample)
{
	Size  size(40, 40);									// 셀 크기
	Mat  trainData, classLable;
	Mat  train_image = imread(train_img, 0);			// 전체 학습영상 로드
	CV_Assert(train_image.data);

	threshold(train_image, train_image, 32, 255, THRESH_BINARY);
	for (int i = 0, k = 0; i<Nclass; i++) {
		for (int j = 0; j< Nsample; j++, k++)
		{
			Point pt(j * size.width, i * size.height);		// 셀 시작좌표
			Rect  roi(pt, size);
			Mat   part = train_image(roi);					// 숫자 영상 분리

			Mat  num = find_number_knn(part);			// 숫자객체 검출
			Mat  data = place_middle_knn(num, size);			// 셀 중심에 숫자 배치 
			trainData.push_back(data);						// 학습 데이터 수집
			classLable.push_back(i);						// 레이블링
		}
	}

	Ptr<ml::KNearest>  knn = ml::KNearest::create();			// k-NN 객체 생성
	knn->train(trainData, ml::ROW_SAMPLE, classLable);		// k-NN 학습
	return knn;
}

Ptr<ml::KNearest> kNN_numbertrain(string train_img, int K, int Nclass, int Nsample)
{
	Size  size(40, 40);									// 셀 크기
	Mat  trainData, classLable;

	for (int i = 0, k = 0; i<Nclass; i++) {
		for (int j = 0; j< Nsample; j++, k++)
		{
			string fn = format("%02d.png", (i*10)+j);
			Mat   part = imread(train_img+fn, 0);

			Mat  num = find_number_knn(part);			// 숫자객체 검출
			Mat  data = place_middle_knn(num, size);			// 셀 중심에 숫자 배치 
			trainData.push_back(data);						// 학습 데이터 수집
			classLable.push_back(i);						// 레이블링
		}
	}

	Ptr<ml::KNearest>  knn = ml::KNearest::create();			// k-NN 객체 생성
	knn->train(trainData, ml::ROW_SAMPLE, classLable);		// k-NN 학습
	return knn;
}
