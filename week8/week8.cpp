// week8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\27318\\Desktop\\大二下网络课程\\数字图像\\第八周\\topic1.JPG", 1);
	Mat dstMat, binMat, outMat;
	resize(srcMat, dstMat, Size(srcMat.cols / 8, srcMat.rows / 8), 0, 0, INTER_LINEAR);
	resize(srcMat, outMat, Size(srcMat.cols / 8, srcMat.rows / 8), 0, 0, INTER_LINEAR);

	cvtColor(dstMat, dstMat, COLOR_BGR2HSV);
	std::vector<cv::Mat> channels;
	cv::split(dstMat, channels);
	cv::Mat S= channels.at(1);
	cv::imshow("S", S);

	threshold(S, binMat, 0, 255, THRESH_OTSU);
	imshow("bin", binMat);
	//通过findContours函数寻找连通域
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(binMat, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		RotatedRect rbox = minAreaRect(contours[i]);
		cout << rbox.size << endl;
		if (fabs(rbox.size.width * 1.0 / rbox.size.height - 1) < 0.2 && rbox.size.width>10) {
			drawContours(S, contours, i, Scalar(0, 255, 255), 1, 8);
			Point2f vtx[4];
			rbox.points(vtx);
			for (int j = 0; j < 4; ++j) {
				cv::line(outMat, vtx[j], vtx[j < 3 ? j + 1 : 0], Scalar(0, 255, 255), 2, CV_AA);
			}
		}
	}
	imshow("result", outMat);
	waitKey(0);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
