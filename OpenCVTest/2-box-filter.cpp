#include <opencv2/highgui.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment (lib, "opencv_world4110d")
#else
#pragma comment (lib, "opencv_world4110")
#endif

using namespace cv;
using namespace std;

// 박스 필터를 구현한 함수.
// 참조 방식으로 매개변수 전달. 함수 내에서 저 변수를 수정할 시 그 원본 또한 수정됨.
void box(const Mat& src, Mat& dst, int a, int b, float sigma) {
    float sigma2 = sigma * sigma;
    dst.create(src.size(), src.type());
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum = 0;
            float wsum = 0;
            for (int t = -b; t <= b; t++) {
                for (int s = -a; s <= a; s++) {
                    int xx = x + s;
                    int yy = y + t;
                    if (xx < 0) xx = -xx;
                    if (xx >= src.cols) xx = src.cols * 2 - xx - 1;
                    if (yy < 0) yy = -yy;
                    if (yy >= src.rows) yy = src.rows * 2 - yy - 1;
                    float w = exp(-(s * s + t * t) / sigma2);
                    sum += w * src.at<float>(yy, xx);
                    wsum += w;
                }
            }
            dst.at<float>(y, x) = sum / wsum;
        }
    }
}


int main()
{   
    //Mat src = imread("../img/paris.jpg", 0); // 컬러로 읽을래요? -> 0(아니요, 흑백)
    Mat src = imread("../img/paris.jpg", 0); 
    if (src.empty()) {
        cout << "Error: Could not load image!" << endl;
        return -1;
    }
    src.convertTo(src, CV_32F, 1 / 255.f);

    Mat dst;
    box(src, dst, 11, 11, 5);
    imshow("window", dst);
    //Mat pp;
    //pow(dst, 2.2, pp);
    //imshow("Image", pp);
    waitKey();
}