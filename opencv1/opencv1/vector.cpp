#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int vector_example()
{
	uchar arr[] = { 10,20,30,40,50 };
	vector<uchar> v1(arr, arr + sizeof(arr) / sizeof(uchar));
	
	v1.push_back(55);
	v1.insert(v1.begin() + 2, 75);
	v1.push_back(100);
	v1.insert(v1.begin() + 5, 150);

	cout << (Mat)v1 << endl;
	return 0;
}