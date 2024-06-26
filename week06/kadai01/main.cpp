#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./ham.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

  // 読み込み失敗の場合
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  // 輝度値の画像
  cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  cv::Mat dst_gaussian_img, tmp_img, dst_img;

  // ガウシアンフィルター処理
  cv::GaussianBlur(gray_img, dst_gaussian_img, cv::Size(3, 3), 0);

  // ソーベルフィルター(縦方向)
  cv::Sobel(dst_gaussian_img, tmp_img, CV_32F, 0, 1);

  cv::convertScaleAbs(tmp_img, dst_img);

  cv::imshow("gaussian", dst_gaussian_img);
  cv::imshow("gaussian + sobel", dst_img);
  cv::waitKey(0);

  return 0;
}
