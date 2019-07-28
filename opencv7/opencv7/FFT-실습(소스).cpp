#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Ideal_Lowpass_Filtering(Mat &imgDFT, double D0);
void ChangeSignOddPositionInXY(Mat &img);
double Phase_Correlation(const Mat &mat_A, const Mat &mat_T, Point *pMaxLoc);

// [실습1] FFT를 이용한 주파수 필터링
void Practice_FFT_Filtering()
{
	Mat src_img = imread("./image/lena.jpg", IMREAD_GRAYSCALE);
	cout << "rows=" << src_img.rows << endl;
	cout << "cols=" << src_img.cols << endl;
	namedWindow("필터링 전", CV_WINDOW_AUTOSIZE);
	imshow("필터링 전", src_img);

	Mat planes[] = {
		Mat_<float>(src_img),
		Mat::zeros(src_img.size(),CV_32F)
	};

	ChangeSignOddPositionInXY(planes[0]);

	Mat imgComplex;
	merge(planes, 2, imgComplex);

	Mat freq;
	dft(imgComplex, freq);
	Ideal_Lowpass_Filtering(freq, 5.0);
	dft(freq, imgComplex, DFT_INVERSE + DFT_SCALE);
	split(imgComplex, planes);
	ChangeSignOddPositionInXY(planes[0]);

	normalize(planes[0], planes[0], 0, 1, CV_MINMAX);
	namedWindow("필터링 후 영상", CV_WINDOW_AUTOSIZE);
	imshow("필터링 후 영상", planes[0]);

	cvWaitKey(0);
	cvDestroyAllWindows();
}


// [실습2] 위상상관을 이용한 매칭
void Pratice_Phase_Correlation_Image()
{
	Mat src_img = imread("./image/numbers.jpg", IMREAD_GRAYSCALE);
	Mat tpl_img = imread("./image/5_2.jpg", IMREAD_GRAYSCALE);
	imshow("srcImage", src_img);
	imshow("tplImage", tpl_img);
	waitKey(0);

	Point max_loc;
	double phaseCorr = Phase_Correlation(src_img, tpl_img, &max_loc);
	printf("phaseCorr=%f\n", phaseCorr);
	printf("max_loc = (%d, %d)\n", max_loc.x, max_loc.y);

	Mat dst_img(src_img.rows, src_img.cols, CV_8UC3);
	cvtColor(src_img, dst_img, CV_GRAY2BGR);
	rectangle(dst_img, max_loc, Point(max_loc.x + tpl_img.cols, max_loc.y + tpl_img.rows), CV_RGB(255, 0, 0));
	imshow("detImage", dst_img);

	waitKey(0);
	destroyAllWindows();
}


// 저주파 성분이 영상의 중앙부에 모이도록 주파수의 원점을 중심으로 이동시킴
void ChangeSignOddPositionInXY(Mat &img)
{
	float fValue;
	// for centering  
	for (int r = 0; r < img.rows; r++) {
		for (int c = 0; c < img.cols; c++) {
			fValue = img.at<float>(r, c);
			if ((r + c) % 2 == 1)
				fValue = -fValue;
			img.at<float>(r, c) = fValue;
		}
	}
}

void Ideal_Lowpass_Filtering(Mat &imgDFT, double D0)
{
	int u, v;
	double D; // distance
	double H;
	double centerU = imgDFT.cols / 2;
	double centerV = imgDFT.rows / 2;
	CvScalar cmplxValue;

	// ideal filter H
	for (v = 0; v < imgDFT.rows; v++) {
		for (u = 0; u < imgDFT.cols; u++) {
			D = sqrt((u - centerU)*(u - centerU) + (v - centerV)*(v - centerV));
			if (D <= D0)
				H = 0.0;
			else
				H = 1.0;
			cmplxValue = imgDFT.at<Vec2f>(v, u);
			cmplxValue.val[0] *= H;
			cmplxValue.val[1] *= H;
			imgDFT.at<Vec2f>(v, u)[0] = cmplxValue.val[0];
			imgDFT.at<Vec2f>(v, u)[1] = cmplxValue.val[1];
		}
	}
}

double Phase_Correlation(const Mat &mat_A, const Mat &mat_B, Point *pMaxLoc)
{
	// 자료형 변환: CV_8UC1 --> CV_32FC1
	Mat mat_floatA, mat_floatB;
	mat_A.convertTo(mat_floatA, CV_32F);	// CV_8UC1 --> CV_32FC1
	mat_B.convertTo(mat_floatB, CV_32F);	// CV_8UC1 --> CV_32FC1

	int	rows = mat_A.rows + mat_B.rows - 1;
	int	cols = mat_A.cols + mat_B.cols - 1;

	// step 1:  Calculate DFT_A of the input mat_A
	Mat planes[] = {
		Mat::zeros(rows, cols, CV_32F),
		Mat::zeros(rows, cols, CV_32F)
	};
	Mat mat_roiA(planes[0], Rect(0, 0, mat_floatA.cols, mat_floatA.rows));
	mat_floatA.copyTo(mat_roiA);
	Mat imgComplex_A;
	merge(planes, 2, imgComplex_A);		// 복소평면(실수부+허수부) 영상
	dft(imgComplex_A, imgComplex_A);	// 2D DFT

										//step 2:  Calculate DFT_B of the input mat_T
	planes[0] = Mat::zeros(rows, cols, CV_32F);
	Mat mat_roiB(planes[0], Rect(0, 0, mat_floatB.cols, mat_floatB.rows));
	mat_floatB.copyTo(mat_roiB);
	Mat imgComplex_B;
	merge(planes, 2, imgComplex_B);		// 복소평면(실수부+허수부) 영상
	dft(imgComplex_B, imgComplex_B);	// 2D DFT

										//step 3: DFT_A = DFT_A * CONJ(DFT_B)
	mulSpectrums(imgComplex_A, imgComplex_B, imgComplex_A, DFT_ROWS,
		true);		// if TRUE, then DFT_A = DFT_A * CONJ(DFT_B) = 상관	
					// if FALSE, then DFT_A = DFT_A * DFT_B		 = 회선	

					//step 4:Normalize by spectrum (pDFT_A* conj(DFT_B))/(| DFT_A * conj(DFT_B) |)
	split(imgComplex_A, planes);

	// Calculate spectrum
	Mat mag;
	magnitude(planes[0], planes[1], mag);	// magnitude 크기 계산 (아래 주석처리된 코드 참조)
	divide(planes[0], mag, planes[0]);
	divide(planes[1], mag, planes[1]);
	merge(planes, 2, imgComplex_A);

	//step 5 : A = IDFT( (pDFT_A* conj(DFT_B))/(| DFT_A * conj(DFT_B) |) )	
	dft(imgComplex_A, imgComplex_A, DFT_INVERSE + DFT_SCALE);		// 2D IDFT
	split(imgComplex_A, planes);

	double   min_val, max_val;
	minMaxLoc(planes[0], &min_val, &max_val, NULL, pMaxLoc);
	return max_val;
}
