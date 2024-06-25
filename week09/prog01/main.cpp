#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "sample.jpg"
#define BIN_TH (100)

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "File is not opened.\n");
    return (-1);
  }

  cv::Mat dst_img, gray_img, bin_img, tmp_img;

  // 入力画像を出力画像にコピー
  dst_img = src_img.clone();

  // グレースケール変換
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 2値化
  cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

  // 2値画像をコピー
  tmp_img = bin_img.clone();

  // 輪郭追跡
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  // 輪郭描画
  for (int i = 0; i < contours.size(); i++) {
    cv::drawContours(dst_img, contours, i, CV_RGB(255, 0, 255), 3);
  }

  // 出力
  cv::imshow("src image", src_img);  // 画像の表示
  cv::imshow("dst image", dst_img);  // 画像の表示
  cv::waitKey();                     // キー入力待ち (止める)
  return 0;
}
