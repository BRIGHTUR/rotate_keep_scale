#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = imread("lena.jpg", 1);
	if (srcMat.empty()) return -1;
	float angle = -10.0, scale = 1;
	Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
	Mat rot = getRotationMatrix2D(center, angle, scale);
	Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//const Mat affine_matrix = getRotationMatrix2D(center, angle, scale);
	warpAffine(srcMat, dstMat, rot, bbox.size());
	imshow("src", srcMat);
	imshow("dst", dstMat);
	waitKey(0);
}