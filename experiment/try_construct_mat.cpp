#include "FaceAlignment.h"
#include <iostream>
using namespace std;
using namespace cv;

int main() {
    Mat_<double> mat(2, 2);

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            mat(i, j) = i + j;
        }
    }

    cout << mat << endl;
    
    return 0;
}