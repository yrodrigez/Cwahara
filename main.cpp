#include "opencv2/opencv.hpp"
#include "KuwaharaFilter.h"

#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;
using namespace cv;

int main() {
    Mat img = imread("nantubos.tif", 1);
    Mat imgGray, dest;
    int kernel = 7;
    imgGray.create(img.size(), CV_8U);
    cvtColor(img, imgGray, CV_BGR2GRAY);

    KuwaharaFilter filter(imgGray, kernel);

    dest = filter.applyFilter();

    imshow("Filtered", dest);
    waitKey();
}