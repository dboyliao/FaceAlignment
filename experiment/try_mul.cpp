#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat_<double> m1 = Mat_<double>(10, 2);
    Mat_<double> m2 = Mat_<double>(10, 2);

    for (int i = 0; i < 10; i++)
    {
        m1(i, 0) = (double)i;
        m1(i, 1) = (double)2 * i;
        m2(i, 0) = (double)10 - i;
        m2(i, 1) = (double)2 * (10 - i);
    }

    Mat_<double> result = m1.mul(m2);

    cout << "m1: " << endl
         << m1 << endl;
    cout << "m2: " << endl
         << m2 << endl;
    cout << "m1.mul(m2): " << endl
         << result << endl;

    return 0;
}