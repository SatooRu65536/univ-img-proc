#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME_1 "./input1.jpg"
#define FILE_NAME_2 "./input2.jpg"
#define ALPHA (0.3)

int main(int argc, const char* argv[]) {
  cv::Mat src_img1 = cv::imread(FILE_NAME_1, 0);
  cv::Mat src_img2 = cv::imread(FILE_NAME_2, 0);

  // 読み込み失敗の場合
  if (src_img1.empty() || src_img2.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat dst_img = cv::Mat(src_img1.size(), CV_8UC1);

  for (int y = 0; y < dst_img.rows; y++) {
    for (int x = 0; x < dst_img.cols; x++) {
      double s1 = src_img1.at<uchar>(y, x);
      double s2 = src_img2.at<uchar>(y, x);

      int s_res = ALPHA * s1 + (1 - ALPHA) * s2;

      dst_img.at<uchar>(y, x) = (uchar)s_res;
    }
  }

  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
