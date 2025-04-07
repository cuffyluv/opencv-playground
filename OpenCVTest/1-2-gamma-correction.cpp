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
    // imshow("Image", src); // 그냥 이거로 show하면 원본 나오고,

    Mat pp;    
    Mat saveimg;

    pow(src, 2.2, pp);
    imshow("MyLittleCat", pp); // 이거를 show하면 사진이 감마 보정되어 좀 더 진하게 나옴.

    // pp.convertTo(saveimg, CV_8U, 255.0);
    // imwrite("../img/res_img/cat_gamma_corrected.jpg", saveimg); // 감마 보정된 이미지를 저장할 수도 있음.

    pow(pp, 1 / 2.2, saveimg);
    saveimg.convertTo(saveimg, CV_8U, 255.0); // 저장할 땐 정규화해둔 거 다시 0~255 범위로 바꿔놔야함.
    imwrite("../img/res_img/cat.jpg", saveimg); // 실제 모니터는 이렇게 원본이 저장됨.
    // 모니터에는 감마 보정된 이미지를 보여주고, 실제 저장할 땐 역보정하여 원본을 저장해야 함.

    waitKey();
}