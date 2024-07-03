#include <stdio.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "challenge.jpg"
#define BIN_TH (200)

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "File is not opened.\n");
    return (-1);
  }

  // グレースケール化
  cv::Mat gray_img;
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 二値化
  cv::Mat bin_img;
  cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

  // 輪郭抽出
  std::vector<std::vector<cv::Point> > contours;
  cv::findContours(bin_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  // 50画素以上だけを残す
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
  int count = 0;
  for (int i = 0; i < contours.size(); i++) {
    double area = cv::contourArea(contours[i]);
    if (area >= 50) {
      count++;
      cv::drawContours(dst_img, contours, i, CV_RGB(255, 255, 255), cv::FILLED);
    }
  }

  printf("count: %d\n", count);

  // 表示
  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey();

  return 0;
}
