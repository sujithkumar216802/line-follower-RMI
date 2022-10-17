#include<opencv2/opencv.hpp>
#include<string>
#include<stdlib.h>

using namespace std;
using namespace cv;

int main() {
	VideoCapture cap;
	int font = FONT_HERSHEY_COMPLEX;
	Mat img, gray, gaussian;
	vector<vector<Point>> contours;	
	vector<Vec4i> hierarchy;
	cap.open(0);
	int outer = 0, inner = 0, outercnt = 0, innercnt = 0;
	float prevarea = 0;

	while (1) {

		cap.read(img);
		resize(img, img, Size(640, 480));

		flip(img, img, 1);
		cvtColor(img, gray, COLOR_BGR2GRAY);

		GaussianBlur(gray, gaussian, Size(15, 15), 0, 0, 0);

		adaptiveThreshold(gaussian, gaussian, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 17, 5);

		findContours(gaussian, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
		string h;

		for (int i = 0; i < contours.size(); i++) {

			approxPolyDP(contours[i], contours[i], 0.01 * arcLength(contours[i], true), true);
			Moments center = moments(contours[i]);
			float x = center.m10 / center.m00;
			float y = center.m01 / center.m00;
			stringstream ss;
			ss << contourArea(contours[i]);

			if (contourArea(contours[i]) < 20000 || contourArea(contours[i]) > 250000 || y > 350 || y < 100)
				continue;

			putText(img, ss.str(), Point(x, y), FONT_HERSHEY_COMPLEX, 2, Vec3d(255, 255, 0));
			circle(img, Point(x, y), 2, Vec3d(255, 0, 0), 1, 8, 0);

			polylines(img, contours[i], true, Vec3d(0, 255, 0), 1);


			double r;


			if (contours[i].size() == 3)
			{
				cout << "Triangle" << endl;//2
				if (contourArea(contours[i]) > prevarea * 0.8)
				{
					prevarea = contourArea(contours[i]);
					if (outer == 2)
						outercnt++;
					else
						outercnt = 1;
					outer = 2;
				}
				else
				{
					if (inner == 2)
						innercnt++;
					else
						innercnt = 1;
					inner = 2;
				}
			}

			else if (contours[i].size() == 4)
			{
				r = (arcLength(contours[i], true) / 4);
				if (r * r > 0.99 * contourArea(contours[i]) && r * r < 1.01 * contourArea(contours[i]))
				{

					cout << "SQUARE" << endl;//3

					if (contourArea(contours[i]) > prevarea * 0.8)
					{
						prevarea = contourArea(contours[i]);
						if (outer == 3)
							outercnt++;
						else
							outercnt = 1;
						outer = 3;
					}
					else
					{
						if (inner == 3)
							innercnt++;
						else
							innercnt = 1;
						inner = 3;
					}

				}


				else
				{

					cout << "Rectangle" << endl;//4

					if (contourArea(contours[i]) > prevarea * 0.8)
					{
						prevarea = contourArea(contours[i]);
						if (outer == 4)
							outercnt++;
						else
							outercnt = 1;
						outer = 4;
					}
					else
					{
						if (inner == 4)
							innercnt++;
						else
							innercnt = 1;
						inner = 4;
					}

				}
			}


			else {
				r = contourArea(contours[i]) / arcLength(contours[i], true);
				r *= 2;
				if (3 * r * r < contourArea(contours[i]) && 3.7 * r * r > contourArea(contours[i]))
				{
					cout << "CIRCLE " << endl;  //0


					if (contourArea(contours[i]) > prevarea * 0.8)
					{
						prevarea = contourArea(contours[i]);
						if (outer == 0)
							outercnt++;
						else
							outercnt = 1;
						outer = 0;
					}
					else
					{
						if (inner == 0)
							innercnt++;
						else
							innercnt = 1;
						inner = 0;
					}
				}

				else
				{
					cout << "SEMI" << endl;//1
					if (contourArea(contours[i]) > prevarea * 0.8)
					{
						prevarea = contourArea(contours[i]);
						if (outer == 1)
							outercnt++;
						else
							outercnt = 1;
						outer = 1;
					}
					else
					{
						if (inner == 1)
							innercnt++;
						else
							innercnt = 1;
						inner = 1;
					}
				}

			}


		}

		if (outercnt > 40 && innercnt > 40)
		{
			cout << "(" << outer << "," << inner << ")";
			break;
		}

		imshow("adaptive", gaussian);
		imshow("img", img);

		waitKey(1);

	}

	return 0;
}