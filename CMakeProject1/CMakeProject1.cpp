// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"

//#include <opencv2/opencv.hpp>
//
//
//using namespace std;
//
//int main()
//{
//	cout << "Hello CMake." << endl;
//	return 0;
//}

//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//using namespace cv;
//using namespace std;
//int main(int argc, char** argv)
//{
//    if (argc != 2)
//    {
//        cout << " Usage: " << argv[0] << " ImageToLoadAndDisplay" << endl;
//        return -1;
//    }
//    Mat image;
//    image = imread(argv[1], IMREAD_COLOR); // Read the file
//    if (image.empty()) // Check for invalid input
//    {
//        cout << "Could not open or find the image" << std::endl;
//        return -1;
//    }
//    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
//    imshow("Display window", image); // Show our image inside it.
//    waitKey(0); // Wait for a keystroke in the window
//    return 0;
//}

//task1

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#include <Eigen/Eigen>;
#include <opencv2/core/eigen.hpp>


void testFunc() {
	Eigen::Vector3i m;
	cv:Vec3i p(200,100,50);
	cv2eigen(p,m);
	auto f = m.norm();
	cout << f;
}

int ChOvFl(int i, int len) { //prevent array quierryng to unavailable elements
	if (i >= len) return len-1;
	if (i < 0) return 0;
	return i;
}

template <typename Templ>
Templ QrAr(int i, int j, cv::Mat const& s) {

	int rows = s.rows;
	int cols = s.cols;

	cv::Size sz = s.size();
	rows = sz.height;
	cols = sz.width;

	i = ChOvFl(i, rows);
	j = ChOvFl(j, cols);
	
	return s.at<Templ>(i,j);
}

//template <typename Abc>
//Abc test1(Mat& a) {
//	a.at(1, 1);
//	return 0;
//}


Eigen::Vector3i defMinPix(Mat& im, int a, int b, int rd) {
	Eigen::Vector3i minPix(255,255,255), currPix(255,255,255);
	for (int i = -rd+a; i <= rd+a; i++) {
		for (int j = -rd+b; j <= rd+b; j++) {
			/*if ( minPix > im.at<int>(ChOvFl(i,im.rows), ChOvFl(j, im.cols))) {
				minPix = im.at<int>(i, j);
			}*/
			cv2eigen(Mat(QrAr<Vec3b>(i, j, im)), currPix);
			if (minPix.norm() > currPix.norm()) {
				minPix = currPix;
			}
		}
	}
	return minPix;
}

void eradeImg(Mat& img, int rd) {
	
	//Vec3b B(200,100,50);
	//float c = (B);
	Mat out(img.rows, img.cols, img.type());
	Mat buff(3, 1, img.type());
	
	for (int i = 0; i < (img.rows - 0); i++) {
		for (int j = 0; j < (img.cols - 0); j++) {
			//out.at<Vec3b>(i, j) = defMinPix<Vec3b>(img, i, j, rd);
			eigen2cv(defMinPix(img, i, j, rd), buff);
			out.at<Vec3b>(i, j) = buff;
		}
	}

	img = out;
	
	return;
}
void procImg(Mat& img) {
	eradeImg(img, 1);
	//erode(img, img, Mat(), Point(-1,-1),1);
	//dilate(img, img, Mat(), Point(-1, -1), 1);

}


int main(int argc, char** argv) {
	if (argc != 2)
		    {
		        cout << " Usage: " << argv[0] << " ImageToLoadAndDisplay" << endl;
		        return -1;
		    }
		    Mat image;
		    image = imread(argv[1], IMREAD_COLOR); // Read the file
		    if (image.empty()) // Check for invalid input
		    {
		        cout << "Could not open or find the image" << std::endl;
		        return -1;
		    }

			namedWindow("Original", WINDOW_AUTOSIZE); // Create a window for display.
			imshow("Original", image); // Show our image inside it.

			//testFunc();
			procImg(image);

		    namedWindow("Processed", WINDOW_AUTOSIZE); // Create a window for display.
		    imshow("Processed", image); // Show our image inside it.
		    waitKey(0); // Wait for a keystroke in the window
		    return 0;

}