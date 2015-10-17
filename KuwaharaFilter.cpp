#include "opencv2/opencv.hpp"
#include "KuwaharaFilter.h"

using namespace cv;

KuwaharaFilter::KuwaharaFilter(const Mat& _image, int & kernel) {
    this->kernel= kernel;
    image= _image.clone();
    wid= image.cols; 
    hei= image.rows;
    pad= this->kernel-1;
}

KuwaharaRegions KuwaharaFilter::getRegions(int& x, int& y){
    KuwaharaRegions regions= KuwaharaRegions(kernel);

    uchar *data = image.data;

    //Update data for each region, pixels that are outside the image's boundary will be ignored.

    //Area 1 (upper left)
    for (int i = (y-pad >=0)? y-pad : 0; i>= 0 && i<=y && i<hei; i++){
        for (int j = ((x-pad >=0) ? x-pad : 0); j>= 0 && j<=x && j<wid; j++) {
            regions.sendData(1,data[(i*wid)+j]);
        }
    }
    //Area 2 (upper right)
    for (int i = (y-pad >=0)? y-pad : 0; i<=y && i<hei; i++){
        for (int j = x; j<=x+pad && j<wid; j++) {
            regions.sendData(2,data[(i*wid)+j]);
        }
    }
    //Area 3 (bottom left)
    for (int i = y; i<=y+pad && i<hei; i++){
        for (int j = ((x-pad >=0) ? x-pad : 0); j<=x && j<wid; j++) {
            regions.sendData(3,data[(i*wid)+j]);
        }
    }
    //Area 0 (bottom right)
    for (int i = y; i<=y+pad && i<hei; i++){
        for (int j = x; j<=x+pad && j<wid; j++) {
            regions.sendData(0,data[(i*wid)+j]);
        }
    }
    return regions;
}


    //Create new image and replace its pixels by the results of Kuwahara filter on the original pixels
Mat KuwaharaFilter::applyFilter(){
    Mat temp;
        temp.create(image.size(), CV_8U);
        uchar* data = temp.data;

        for (int i= 0; i<hei; i++) {
            for (int j = 0; j<wid; j++){
                data[i*wid+j] = getRegions(j,i).result();
            }
        }
        return temp;
}