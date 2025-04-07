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

    // dft() 함수는 OpenCV에서 DFT(Discrete Fourier Transform, 이산 푸리에 변환) 을 수행하는 함수.
    // 이 함수는 이미지나 신호를 공간(domain) → 주파수(domain) 로 변환하는 데 사용됨.
    dft(src, dst, DFT_COMPLEX_OUTPUT);
    // 출력 형식 옵션: 복소수(complex number)로 출력 하겠다는 의미.
    // dst는, 크기는 원본과 같은데, 픽셀 당 값이 두 개 들어가 있음. 실수와 허수.
        src.convertTo(src, CV_32F, 1 / 255.f); 

    Mat mag;
    Mat chan[2];
    split(dst, chan); // dst를 chan으로 쪼개라.
    magnitude(chan[0], chan[1], mag);
    Mat rec;
    idft(dst, rec, DFT_REAL_OUTPUT|DFT_SCALE); // -> DFT한 걸 IDFT했더니 복원됐다.

    imshow("window", rec);
    // imshow("window", mag); // 하얀 배경에 검정 점들이 나옴 -> 무슨 의민지 알 수 없음.

    waitKey();



}