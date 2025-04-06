﻿#include <opencv2/highgui.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment (lib, "opencv_world4110d")
#else
#pragma comment (lib, "opencv_world4110")
#endif

using namespace cv;
using namespace std;

// 가우시안 필터를 구현한 함수. 모든 픽셀을 순회하는데, 
// 각 픽셀 (x, y)를 중심으로 (2*a + 1) x (2*b + 1) 크기의 필터를 가지고 가우시안-필터링함.
// 경계에서는 제로 패딩 대신 반사 패딩(Reflection padding) 방식을 사용하고 있음.
// 
// src: 입력 이미지, dst: 출력 이미지.
// a: x축 커널 반지름, b: y축 커널 반지름.
// sigma: 가우시안 필터링 식에 쓰이는 가중치 조절 파라미터 시그마.
// 
// 시그마는 분포의 '퍼짐 정도'를 결정하는 값으로,
// 시그마가 작으면: 중심 픽셀에 매우 큰 가중치를 주고 주변 픽셀은 거의 무시되어, 블러 정도가 약해짐. 엣지 디테일이 잘 보존됨.
// 시그마가 크면: 중신 픽셀뿐 아니라 주변도 꽤 큰 가중치를 주어, 블러 정도가 강해짐. 이미지 전체가 부드럽게 퍼지고, 엣지 디테일이 많이 사라짐.
// 
// 참조 방식으로 매개변수를 전달하고 있음. 함수 내에서 저 변수를 수정할 시 그 원본 또한 수정됨.
void gaussian(const Mat& src, Mat& dst, int a, int b, float sigma) {
    float sigma2 = sigma * sigma;
    dst.create(src.size(), src.type()); // src와 동일한 크기 및 타입으로 행렬(이미지) dst를 만듦.

    // 모든 픽셀에 대해 순회함.
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum = 0;
            float wsum = 0;

            // 아래 계산을 통해 필터의 왼쪽 아래부터 오른쪽 위까지의 필터링 계수 w를 구하고 있음.
            // 커널 영역 탐색 (y-b ~ y+b)
            for (int t = -b; t <= b; t++) {
                // 커널 영역 탐색 (x-a ~ x+a)
                for (int s = -a; s <= a; s++) {
                    // 각 상하좌우 경계들에 대한 반사 패딩 적용.
                    int xx = x + s;
                    int yy = y + t;
                    if (xx < 0) xx = -xx; // 좌측
                    if (xx >= src.cols) xx = src.cols * 2 - xx - 1; // 우측
                    if (yy < 0) yy = -yy; // 위쪽
                    if (yy >= src.rows) yy = src.rows * 2 - yy - 1; // 아래쪽

                    // 본격적인 가중치 계산 및 누적.
                    float w = exp(-(s * s + t * t) / sigma2); // 가중치 w를 구함.
                    sum += w * src.at<float>(yy, xx); // 그 가중치를 각 픽셀에 곱한 값을 차곡차곡 더함.
                    wsum += w; // 얘는 나중에 정규화하기 위해 사용한 가중치 w들의 합을 구함.
                }
            }
            // 아까 구한 가중치w들의 합으로 정규화 후 그 결과를 dst에 저장.
            dst.at<float>(y, x) = sum / wsum;
        }
    }
}

// 참고) Mat.at<type>(row, col) 함수: 특정 위치의 값에 접근할 때 쓰는 함수.
// <type>에는 해당 이미지의 타입을, (row, col)에는 좌표를 넣어주면 됨.
// ex1. src.at<float>(y, x) → float 타입 이미지 (CV_32FC1)
// ex2. src.at<uchar>(y, x) → 8비트 흑백 이미지 (CV_8UC1)
// ex3. src.at<cv::Vec3b>(y, x) → 8비트 컬러 이미지 (CV_8UC3)

int main()
{   
    // 두 번째 인자는 '컬러로 읽을까요?' 하고 물어보는 거임. 0: 흑백, Default: 컬러.
    // 필터 구현을 컬러로 할 거면 RGB값을 각각 다뤄줘야 함. 귀찮아!!
    // 그래서 우리는 흑백으로 밝기 하나만 가지고 다룰 거임. 따라서 인자를 0으로 넘겨줌. 
    Mat src = imread("../img/paris.jpg", 0); 
    if (src.empty()) {
        cout << "Error: Could not load image!" << endl;
        return -1;
    }
    src.convertTo(src, CV_32F, 1 / 255.f); 

    Mat dst;
    // 인자: 원본 이미지, 결과 이미지, 필터 너비, 필터 높이, 가중치 조절 파라미터 시그마.
    gaussian(src, dst, 11, 11, 5); 
    imshow("window", dst);
    //Mat pp;
    //pow(dst, 2.2, pp);
    //imshow("Image", pp); // 감마 보정
    waitKey();
}