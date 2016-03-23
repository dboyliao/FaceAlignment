#include "FaceAlignment.h"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat_<double> matrix1 = Mat_<double>(2, 10, CV_64FC1);
    Mat_<double> matrix2 = Mat_<double>(2, 10, CV_64FC1);

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 10; j++){
            matrix1(i, j) = i + j;
            matrix2(i, j) = 2*(i + j);
        }
    }

    Mat_<double> rotation;
    double scale;
    SimilarityTransform(matrix1, matrix2, rotation, scale);

    cout << "matrix1: " << endl << " " << matrix1 << endl << endl;
    cout << "matrix2: " << endl << " " << matrix2 << endl << endl;
    cout << "rotation: " << endl << " " << rotation << endl << endl;
    cout << "rotation * rotation': " << endl << " " << rotation.mul(rotation) << endl << endl;
    cout << "scale: " << endl << " " << scale << endl << endl;
    return 0;
}
