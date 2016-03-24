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
        }
    }

    Mat_<double> rotation_origin = Mat_<double>(2, 2, CV_64FC1);
    rotation_origin(0, 0) = 0.5;
    rotation_origin(0, 1) = -0.886;
    rotation_origin(1, 0) = 0.886;
    rotation_origin(1, 1) = 0.5;
    
    cout << "rotation_origin: " << endl << " " << endl << rotation_origin << endl << endl;
    matrix2 = rotation_origin * matrix1;

    Mat_<double> rotation;
    double scale;
    SimilarityTransform(matrix1, matrix2, rotation, scale);
    Mat_<double> result = scale * rotation * matrix2;

    cout << "matrix1: " << endl << " " << matrix1 << endl << endl;
    cout << "matrix2: " << endl << " " << matrix2 << endl << endl;
    cout << "rotation: " << endl << " " << rotation << endl << endl;
    cout << "rotation * rotation': " << endl << " " << rotation * rotation.t() << endl << endl;
    cout << "scale: " << endl << " " << scale << endl << endl;
    cout << "result: " << endl << " " << result << endl << endl;
    return 0;
}
