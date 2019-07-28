#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat find_number(Mat part);
Mat  place_middle(Mat number, Size new_size);

void collect_trainImage(Mat& trainingData, Mat& labels, int Nimages = 100)
{
	for (int i = 0; i< Nimages; i++)
	{
		string fname = format("./image/train_numbers/%02d.png", i);// 학습영상 파일
		Mat img = imread(fname, 0);
		CV_Assert(img.data);

		Mat  num = find_number(img);// 숫자객체 검색
		Mat  data = place_middle(num, Size(40, 40));

		int label = i/10;

		trainingData.push_back(data);
		labels.push_back(label);
	}
	trainingData.convertTo(trainingData, CV_32FC1);
}

void write_traindata(string fn, Mat trainingData, Mat classes)
{
	FileStorage fs(fn, FileStorage::WRITE);
	fs << "TrainingData" << trainingData;
	fs << "classes" << classes;
	fs.release();
}

// xml 데이터 읽기
void  read_trainData(string fn, Mat & trainingData, Mat & lables = Mat())
{
	FileStorage fs(fn, FileStorage::READ);
	CV_Assert(fs.isOpened());

	fs["TrainingData"] >> trainingData;
	fs["classes"] >> lables;
	fs.release();

	trainingData.convertTo(trainingData, CV_32FC1);
}

Ptr<ml::SVM>  SVM_create_(int type, int max_iter, double epsilon)
{
	Ptr<ml::SVM> svm = ml::SVM::create();		// SVM 객체 선언
												// SVM 파라미터 지정
	svm->setType(ml::SVM::C_SVC);				// C-Support Vector Classification				
	svm->setKernel(ml::SVM::LINEAR);			// 선형 SVM 
	svm->setGamma(1);							// 커널함수의 감마값
	svm->setC(1);								// 최적화를 위한 C 파리미터

	TermCriteria criteria(type, max_iter, epsilon);
	svm->setTermCriteria(criteria);				// 반복 알고리즘의 조건
	return svm;
}

void train_number()
{
	Mat trainingData, labels;
	collect_trainImage(trainingData, labels);

	// SVM 객체 선언 
	Ptr<ml::SVM> svm = SVM_create_(CV_TERMCRIT_ITER, 1000, 0.01);
	svm->train(trainingData, ml::ROW_SAMPLE, labels);	// 학습수행
	svm->save("./NUMBERtrain.xml");
}

