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
    if (src.empty()) { 
        cout << "Error: Could not load image!" << endl;
        return -1;
    }

    src.convertTo(src, CV_32F, 1 / 255.f);
    // imshow("Image", src); // �׳� �̰ŷ� show�ϸ� ���� ������,

    Mat pp;    
    Mat saveimg;

    pow(src, 2.2, pp);
    imshow("MyLittleCat", pp); // �̰Ÿ� show�ϸ� ������ ���� �����Ǿ� �� �� ���ϰ� ����.

    // pp.convertTo(saveimg, CV_8U, 255.0);
    // imwrite("../img/res_img/cat_gamma_corrected.jpg", saveimg); // ���� ������ �̹����� ������ ���� ����.

    pow(pp, 1 / 2.2, saveimg);
    saveimg.convertTo(saveimg, CV_8U, 255.0); // ������ �� ����ȭ�ص� �� �ٽ� 0~255 ������ �ٲ������.
    imwrite("../img/res_img/cat.jpg", saveimg); // ���� ����ʹ� �̷��� ������ �����.
    // ����Ϳ��� ���� ������ �̹����� �����ְ�, ���� ������ �� �������Ͽ� ������ �����ؾ� ��.

    waitKey();
}