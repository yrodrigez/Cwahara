#include "opencv2/opencv.hpp"
#include "KuwaharaRegions.h"

using namespace cv;

class KuwaharaFilter{
private:
    int wid;
    int hei;
    int pad; 
    int kernel;
    Mat image;

public:
    KuwaharaRegions getRegions(int & x, int & y);
    KuwaharaFilter(const Mat & image, int & _kernel);
    Mat applyFilter();
};
