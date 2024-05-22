#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./apple_grayscale.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, 0);

  // 読み込み失敗の場合
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  // フィルター処理
  cv::GaussianBlur(src_img, dst_img, cv::Size(3, 3), 0);

  cv::imshow("output", dst_img);
  cv::waitKey(0);

  return 0;
}
