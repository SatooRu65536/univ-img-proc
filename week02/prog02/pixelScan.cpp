#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME_INPUT "./aquarium.jpg"
#define FILE_NAME_OUTPUT "./aquarium_out.jpg"
#define WINDOW_NAME "output"

int main(int argc, const char* argv[]) {
  int x = 0, y = 0;

  // 画像の入力
  cv::Mat src_img;  // 画像の型と変数

  src_img = cv::imread(FILE_NAME_INPUT);  // 画像の読み込み
  if (src_img.empty()) {                  // 入力失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
  for (y = 0; y < src_img.rows; y++) {
    for (x = 0; x < src_img.cols; x++) {
      cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);

      int line_width = 10;
      if ((x < line_width || y < line_width) ||
          (x > src_img.cols - line_width || y > src_img.rows - line_width)) {
        s[0] = 0;
        s[1] = 0;
        s[2] = 0;
      } else {
        s[0] = s[0];
        s[1] = s[1];
        s[2] = s[2];
      }

      dst_img.at<cv::Vec3b>(y, x) = s;
    }
  }

  cv::imshow(FILE_NAME_INPUT, src_img);   // 画像の表示
  cv::imshow(FILE_NAME_OUTPUT, dst_img);  // 画像の表示
  cv::waitKey();                          // キー入力待ち (止める)

  return 0;
}
