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

  cv::Mat dst_img3 = cv::Mat(src_img.size(), CV_8UC1);
  cv::Mat dst_img5 = cv::Mat(src_img.size(), CV_8UC1);

  double filter_h3[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      filter_h3[i][j] = 1.0 / 9.0;
    }
  }

  double filter_h5[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      filter_h5[i][j] = 1.0 / 25.0;
    }
  }

  cv::Mat kernel3 = cv::Mat(3, 3, CV_32F, filter_h3);
  cv::Mat kernel5 = cv::Mat(5, 5, CV_32F, filter_h5);

  // 正規化
  cv::normalize(kernel3, kernel3, 1.0, 0.0, cv::NORM_L1);
  cv::normalize(kernel5, kernel5, 1.0, 0.0, cv::NORM_L1);

  // フィルター処理
  cv::filter2D(src_img, dst_img3, -1, kernel3);
  cv::filter2D(src_img, dst_img5, -1, kernel5);

  cv::imshow("output 3x3", dst_img3);
  cv::imshow("output 5x5", dst_img5);
  cv::waitKey(0);

  return 0;
}
