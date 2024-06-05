#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./moon-is-kirei.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, 0);

  // 読み込み失敗の場合
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat dst_gaussian_img = cv::Mat(src_img.size(), CV_8UC1);
  cv::Mat tmp_img;
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  // ガウシアンフィルター処理
  cv::GaussianBlur(src_img, dst_gaussian_img, cv::Size(3, 3), 0);

  // ソーベルフィルター
  cv::Sobel(dst_gaussian_img, tmp_img, CV_32F, 1, 0);

  cv::convertScaleAbs(tmp_img, dst_img);

  cv::imshow("gaussian", dst_gaussian_img);
  cv::imshow("gaussian + sobel", dst_img);
  cv::waitKey(0);

  return 0;
}
