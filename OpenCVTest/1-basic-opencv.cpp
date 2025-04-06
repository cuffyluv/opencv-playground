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
    // imshow("Image", src); // 그냥 이거로 show하면 원본 나오고,

    Mat pp;
    pow(src, 2.2, pp);
    imshow("Image", pp); // 이거를 show하면 사진이 좀 더 진하게 나옴.

    waitKey();
    //std::cout << "Hello World!\n";
}