#include <opencv2/highgui.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment (lib, "opencv_world4110d")
#else
#pragma comment (lib, "opencv_world4110")
#endif

using namespace cv;
using namespace std;

// �ڽ� ���͸� ������ �Լ�. ��� �ȼ��� ��ȸ�ϴµ�, 
// �� �ȼ� (x, y)�� �߽����� (2*a + 1) x (2*b + 1) ũ���� ���͸� ������ �ڽ�-���͸���.
// ��迡���� ���� �е� ��� �ݻ� �е�(Reflection padding) ����� ����ϰ� ����.
// 
// src: �Է� �̹���, dst: ��� �̹���.
// a: x�� Ŀ�� ������, b: y�� Ŀ�� ������.
// 
// ���� ������� �Ű������� �����ϰ� ����. �Լ� ������ �� ������ ������ �� �� ���� ���� ������.
void box(const Mat& src, Mat& dst, int a, int b) {
    dst.create(src.size(), src.type()); // src�� ������ ũ�� �� Ÿ������ ���(�̹���) dst�� ����.

    // ��� �ȼ��� ���� ��ȸ��.
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float sum = 0;

            // �Ʒ� ����� ���� ������ ���� �Ʒ����� ������ �������� ���͸� ����� ���ϰ� ����.
            // Ŀ�� ���� Ž�� (y-b ~ y+b)
            for (int t = -b; t <= b; t++) {
                // Ŀ�� ���� Ž�� (x-a ~ x+a)
                for (int s = -a; s <= a; s++) {
                    // �� �����¿� ���鿡 ���� �ݻ� �е� ����.
                    int xx = x + s;
                    int yy = y + t;
                    if (xx < 0) xx = -xx; // ����
                    if (xx >= src.cols) xx = src.cols * 2 - xx - 1; // ����
                    if (yy < 0) yy = -yy; // ����
                    if (yy >= src.rows) yy = src.rows * 2 - yy - 1; // �Ʒ���

                    // ����ġ�� �ȼ��� ���� ��� ��� �� ����.
                    // ���⼭, ����ġ�� �� ���� 1�� �Ǿ�� �ϹǷ� ���� ũ��� ����ȭ.
                    sum += 1 / float((2 * a + 1) * (2 * b + 1)) * src.at<float>(yy, xx);
                }
            }
            // �Ʊ� ���� ����ġ�� ���� �ȼ������� ���� ���� ��� �̹����� ����.
            dst.at<float>(y, x) = sum;
        }
    }
}

// ����) Mat.at<type>(row, col) �Լ�: Ư�� ��ġ�� ���� ������ �� ���� �Լ�.
// <type>���� �ش� �̹����� Ÿ����, (row, col)���� ��ǥ�� �־��ָ� ��.
// ex1. src.at<float>(y, x) �� float Ÿ�� �̹��� (CV_32FC1)
// ex2. src.at<uchar>(y, x) �� 8��Ʈ ��� �̹��� (CV_8UC1)
// ex3. src.at<cv::Vec3b>(y, x) �� 8��Ʈ �÷� �̹��� (CV_8UC3)

int main()
{
    // �� ��° ���ڴ� '�÷��� �������?' �ϰ� ����� ����. 0: ���, Default: �÷�.
    // ���� ������ �÷��� �� �Ÿ� RGB���� ���� �ٷ���� ��. ������!!
    // �׷��� �츮�� ������� ��� �ϳ��� ������ �ٷ� ����. ���� ���ڸ� 0���� �Ѱ���. 
    Mat src = imread("../img/cat.jpg", 0);
    if (src.empty()) {
        cout << "Error: Could not load image!" << endl;
        return -1;
    }
    src.convertTo(src, CV_32F, 1 / 255.f);

    Mat dst;
    // ����: ���� �̹���, ��� �̹���, ���� �ʺ�, ���� ����.
    box(src, dst, 4, 4); // �̰� 0, 0���� �ָ��� �׳� �����̶� �Ȱ��� ����.
    imshow("MyLittleCat", dst);

    Mat saveimg;
    dst.convertTo(saveimg, CV_8U, 255.0);
    imwrite("../img/res_img/cat_box_filtered.jpg", saveimg);
    waitKey();
}