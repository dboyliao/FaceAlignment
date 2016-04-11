#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    vector<double> v1(10);

    for (int i = 0; i < 10; i++)
    {
        v1[i] = (double)i;
    }

    normalize(v1, v1); // v1 / sqrt((v1**2).sum())
    for (int i = 0; i < 10; i++)
    {
        cout << v1[i] << endl;
    }

    return 0;
}