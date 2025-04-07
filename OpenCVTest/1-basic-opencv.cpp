#include <opencv2/highgui.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment (lib, "opencv_world4110d")
#else
#pragma comment (lib, "opencv_world4110")
#endif

using namespace cv;
using namespace std;


int main()
{
    Mat src = imread("../img/cat.jpg");
    if (src.empty()) {  // 이미지가 비어 있는지 체크
        cout << "Error: Could not load image!" << endl;
        return -1;
    }

    // 픽셀값 0~1 float 범위로 정규화. 이제 우리의 이미지 src는 float 타입이 됨.
    src.convertTo(src, CV_32F, 1 / 255.f); 
    imshow("MyLittleCat", src);

    waitKey();
    //std::cout << "Hello World!\n";
}