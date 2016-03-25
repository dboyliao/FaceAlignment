#include "experiment.h"

using namespace std;
using namespace cv;

int main(){

    Mat_<int> m = Mat_<int>(10, 1);

    for (int i = 0; i < m.rows; i++){
        m(i, 0) = i;
    }

    cout << m << endl;
    cout << "sum is to calulate the sum of each channels (1 ~ 4)." << endl;
    cout << "sum(m)[0]: " << endl << sum(m)[0] << endl;
    return 0;
}