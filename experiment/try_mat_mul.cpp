#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cstdio>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    Mat_<double> m1 = Mat_<double>(3, 5); // 3 x 5 matrix
    Mat_<double> m2 = Mat_<double>(5, 3); // 5 x 3 matrix

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            m1(i, j) = (i + 1) * (i + 1) * (j + 1);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m2(i, j) = (i + 1) * (j + 1);
        }
    }

    cout << "m1 (3x5): " << endl
         << m1 << endl
         << endl;
    cout << "m1.rows: " << m1.rows << endl;
    cout << "m1.cols: " << m1.cols << endl;
    cout << "m2 (5x3): " << endl
         << m2 << endl
         << endl;
    cout << "m2.rows: " << m2.rows << endl;
    cout << "m2.cols: " << m2.cols << endl;
    cout << "m1*m2: " << endl
         << m1 * m2 << endl
         << endl;
    cout << (m1 * m2).size() << endl;
    cout << "m2*m1: " << endl
         << m2 * m1 << endl
         << endl;
    cout << (m2 * m1).size() << endl;
}
