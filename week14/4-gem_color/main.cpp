#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "gem1.jpg"

#define R_MIN (0)    // Rの最小値
#define R_MAX (50)   // Rの最大値
#define G_MIN (50)   // Gの最小値
#define G_MAX (100)  // Gの最大値
#define MAX_VAL (255)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

enum {
  BLUE,
  GREEN,
  RED,
};

int main(int argc, const char* argv[]) {
  // 1. 画像を入力
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

  if (src_img.empty()) {
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }

  // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
  cv::Mat dst_img = cv::Mat(src_img.rows, src_img.cols, CV_8UC1, cv::Scalar(0));

  // 3. しきい値処理
  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      cv::Vec3b p = src_img.at<cv::Vec3b>(y, x);

      if (p[RED] <= R_MIN || p[RED] >= R_MAX) continue;
      if (p[GREEN] <= G_MIN || p[GREEN] >= G_MAX) continue;

      dst_img.at<uchar>(y, x) = MAX_VAL;
    }
  }

  // 4. 表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::waitKey();  // キー入力待ち (止める)

  return 0;
}
