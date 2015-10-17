#include "opencv2/opencv.hpp"
#include "KuwaharaRegions.h"
#include <cmath>

KuwaharaRegions::KuwaharaRegions(int & kernel) {
    this->kernel= kernel;
    for (int i = 0; i<4; i++) {
        area[i] = new int[kernel*kernel];
        tamano[i] = 0;
        sumatorias[i] = 0;
        varianzas[i] = 0.0;
     }
}

//Update data, increase the tamano of the area, update the sumatorias
void KuwaharaRegions::sendData(int area, uchar &data){
        this->area[area][tamano[area]] = data;
        sumatorias[area] += data;
        tamano[area]++;
}

//Calculate the variance of each area
double KuwaharaRegions::var(int &area) {
    int media = sumatorias[area]/tamano[area];
    double temp = 0;
    for (int i = 0; i<tamano[area]; i++) {
        temp+= (this->area[area][i] - media) * (this->area[area][i] - media);
    }
    if (tamano[area]==1) return 1.7e38; //If there is only one pixel inside the region then return the maximum of double
                                           //So that with this big number, the region will never be considered in the below minVar()
        return sqrt(temp/(tamano[area]-1));
    }

    //Call the above function to calc the variances of all 4 areas
void KuwaharaRegions::calcVar() {
    for (int i = 0; i<4; i++) {
        varianzas[i] = var(i);
    }
}
    //Find out which regions has the least variance
int KuwaharaRegions::minVar() {
    calcVar();
    int i = 0;
    double var = varianzas[0];
    if (var > varianzas[1]) {var = varianzas[1]; i = 1;}
    if (var > varianzas[2]) {var = varianzas[2]; i = 2;}
    if (var > varianzas[3]) {var = varianzas[3]; i = 3;}
    return i;
}

    //Return the mean of that regions
uchar KuwaharaRegions::result(){
    int i = minVar();
    return cv::saturate_cast<uchar> ((double) (sumatorias[i] *1.0 / tamano[i]));
}
