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
    if (src.empty()) {  // �̹����� ��� �ִ��� üũ
        cout << "Error: Could not load image!" << endl;
        return -1;
    }

    // �ȼ��� 0~1 float ������ ����ȭ. ���� �츮�� �̹��� src�� float Ÿ���� ��.
    src.convertTo(src, CV_32F, 1 / 255.f); 
    imshow("MyLittleCat", src);

    waitKey();
    //std::cout << "Hello World!\n";
}