#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME_INPUT "./in.jpg"
#define FILE_NAME_OUTPUT "./out.jpg"
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

  fprintf(stderr, "width=%d, height=%d\n", src_img.cols, src_img.rows);

  int cell_size = 20;
  int gray_level = 16;
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);
  for (y = 0; y < src_img.rows; y += cell_size) {
    for (x = 0; x < src_img.cols; x += cell_size) {
      int sum = 0;
      for (int x2 = 0; x2 < cell_size; x2++) {
        for (int y2 = 0; y2 < cell_size; y2++) {
          cv::Vec3b s = src_img.at<cv::Vec3b>(y + y2, x + x2);
          sum += s[0] + s[1] + s[2];
        }
      }

      for (int x2 = 0; x2 < cell_size; x2++) {
        for (int y2 = 0; y2 < cell_size; y2++) {
          cv::Vec3b s = src_img.at<cv::Vec3b>(y + y2, x + x2);
          int color =
              ((sum / (cell_size * cell_size * 3) / (256 / gray_level))) *
              (256 / gray_level);
          s[0] = color;
          s[1] = color;
          s[2] = color;
          dst_img.at<cv::Vec3b>(y + y2, x + x2) = s;
        }
      }
    }
  }

  cv::imshow(FILE_NAME_INPUT, src_img);   // 画像の表示
  cv::imshow(FILE_NAME_OUTPUT, dst_img);  // 画像の表示
  cv::imwrite(FILE_NAME_OUTPUT, dst_img); // 画像の保存
  cv::waitKey();                          // キー入力待ち (止める)

  return 0;
}
