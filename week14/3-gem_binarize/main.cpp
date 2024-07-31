#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "gem1.jpg"

#define TH (20)
#define MAX_VAL (255)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_GRAYSCALE "grayimage"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* argv[]) {
  // 1. 入力画像をカラーで入力
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

  // 2. グレースケール画像
  cv::Mat gray_img;
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 3. 二値化
  cv::Mat res_img, dst_img;
  cv::threshold(gray_img, res_img, TH, MAX_VAL, cv::THRESH_BINARY);
  cv::bitwise_not(res_img, dst_img);

  // 4. 表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_GRAYSCALE, gray_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::waitKey();  // キー入力待ち (止める)

  return 0;
}
