#include "FaceAlignment.h"
#include <iostream>
#include <string>
using namespace std;
using namespace cv;

int main()
{
    ifstream fin;
    fin.open("./COFW_Dataset/keypoints.txt");

    Mat_<double> matrix1 = Mat_<double>(29, 2, CV_64FC1);
    Mat_<double> matrix2 = Mat_<double>(29, 2, CV_64FC1);

    for (int i = 0; i < 29; i++)
    {
        fin >> matrix1(i, 0);
    }

    for (int i = 0; i < 29; i++)
    {
        fin >> matrix1(i, 1);
    }

    for (int i = 0; i < 29; i++)
    {
        fin >> matrix2(i, 0);
    }

    for (int i = 0; i < 29; i++)
    {
        fin >> matrix2(i, 1);
    }
    fin.close();

    Mat_<double> rotation;
    double scale;
    SimilarityTransform(matrix1, matrix2, rotation, scale);
    // Mat_<double> result = scale * rotation * matrix2;

    cout << "matrix1: " << endl
         << " " << matrix1 << endl
         << endl;
    cout << "matrix2: " << endl
         << " " << matrix2 << endl
         << endl;
    cout << "rotation: " << endl
         << " " << rotation << endl
         << endl;
    cout << "rotation * rotation': " << endl
         << " " << rotation * rotation.t() << endl
         << endl;
    cout << "scale: " << endl
         << " " << scale << endl
         << endl;
    // cout << "result: " << endl << " " << result << endl << endl;
    return 0;
}
