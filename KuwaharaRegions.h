#include "opencv2/opencv.hpp"

class KuwaharaRegions{
private:
    int* area[4];
    int tamano[4];
    unsigned long long sumatorias[4];
    double varianzas[4];
    int kernel;
public:
    KuwaharaRegions(int & kernel);
    void sendData(int area, uchar & data);
    double var(int & area); 
    void calcVar();
    int minVar();
    uchar result();
};