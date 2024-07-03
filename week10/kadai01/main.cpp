#include <stdio.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "issue1.jpg"

// 二値化閾値
#define BIN_TH (100)

struct Feature {
  int index;
  int size;
};

int main(int argc, const char* argv[]) {
  // 画像の宣言
  cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

  // 色値の設定
  cv::Scalar color[] = {
      CV_RGB(255, 0, 0),   //
      CV_RGB(0, 255, 0),   //
      CV_RGB(0, 0, 255),   //
      CV_RGB(255, 0, 255)  //
  };

  // 輪郭の座標リストの宣言

  // 画像の入力 (カラーで入力)
  src_img = cv::imread(FILE_NAME);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "File is not opened.\n");
    return (-1);
  }

  // グレースケール化
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 二値化 (固定閾値で実装．閾値: 100)
  cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

  dst_img = bin_img.clone();
  tmp_img = bin_img.clone();

  // 膨超
  cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 20);
  cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 20);

  // 二値画像コピー

  cv::Mat output_img = cv::Mat::zeros(dst_img.size(), CV_8UC3);

  // 輪郭抽出
  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(dst_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  // 輪郭の描画
  for (int i = 0; i < contours.size(); i++) {
    double area = cv::contourArea(contours[i]);
    double circularity =
        4 * M_PI * area / pow(cv::arcLength(contours[i], true), 2);

    if (circularity < 0.8) {
      cv::drawContours(output_img, contours, i, color[i % 4], cv::FILLED);
    }
  }

  // 重なる部分だけを残す
  cv::Mat masked_img = cv::Mat::zeros(dst_img.size(), CV_8UC3);
  cv::bitwise_and(src_img, output_img, masked_img);

  // 表示
  cv::imshow("output", masked_img);
  cv::waitKey();

  return 0;
}
