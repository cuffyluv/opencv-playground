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
    Mat src = imread("../img/paris.jpg", 0);
    if (src.empty()) {
        cout << "Error: Could not load image!" << endl;
        return -1;
    }
    src.convertTo(src, CV_32F, 1 / 255.f);

    Mat dst;

    // dft() �Լ��� OpenCV���� DFT(Discrete Fourier Transform, �̻� Ǫ���� ��ȯ) �� �����ϴ� �Լ�.
    // �� �Լ��� �̹����� ��ȣ�� ����(domain) �� ���ļ�(domain) �� ��ȯ�ϴ� �� ����.
    dft(src, dst, DFT_COMPLEX_OUTPUT);
    // ��� ���� �ɼ�: ���Ҽ�(complex number)�� ��� �ϰڴٴ� �ǹ�.
    // dst��, ũ��� ������ ������, �ȼ� �� ���� �� �� �� ����. �Ǽ��� ���.
        src.convertTo(src, CV_32F, 1 / 255.f); 

    Mat mag;
    Mat chan[2];
    split(dst, chan); // dst�� chan���� �ɰ���.
    magnitude(chan[0], chan[1], mag);
    Mat rec;
    idft(dst, rec, DFT_REAL_OUTPUT|DFT_SCALE); // -> DFT�� �� IDFT�ߴ��� �����ƴ�.

    imshow("window", rec);
    // imshow("window", mag); // �Ͼ� ��濡 ���� ������ ���� -> ���� �ǹ��� �� �� ����.

    waitKey();



}