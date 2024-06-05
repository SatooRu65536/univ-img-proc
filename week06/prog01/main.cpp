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

  cv::Mat tmp_img;
  cv::Mat dst_img;

  double filter_h[3][3] = {
      {0, 0, 0},   //
      {-1, 0, 1},  //
      {0, 0, 0}    //
  };
  cv::Mat kernel = cv::Mat(3, 3, CV_64F, filter_h);

  // 正規化
  //   cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);

  // フィルター処理
  cv::filter2D(src_img, tmp_img, CV_64F, kernel);
  cv::convertScaleAbs(tmp_img, dst_img);

  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
