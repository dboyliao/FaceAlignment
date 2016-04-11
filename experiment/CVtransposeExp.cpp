#include "FaceAlignment.h"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Mat_<double> mat = Mat_<double>(5, 3, CV_64FC1);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            mat(i, j) = i * 3 + j;
        }
    }

    transpose(mat, mat);
    cout << "mat:" << endl
         << " " << endl
         << mat << endl
         << endl;
    return 0;
}
