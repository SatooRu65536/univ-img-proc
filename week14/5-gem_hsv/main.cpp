#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "gem1.jpg"

#define HUE_MIN (20.0)   // Hの最小値
#define HUE_MAX (60.0)   // Hの最大値
#define SAT_MIN (100.0)  // Sの最小値
#define SAT_MAX (200.0)  // Sの最小値
#define MAX_VAL (255)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

enum {
  HUE,
  SAT,
  VAL,
};

int main(int argc, const char* argv[]) {
  // 1. 画像を入力
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }
  // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
  cv::Mat dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

  // 3. 色変換 (BGR → HSV)
  cv::Mat hsv_img;
  cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

  // 4. しきい値処理
  for (int y = 0; y < hsv_img.rows; y++) {
    for (int x = 0; x < hsv_img.cols; x++) {
      cv::Vec3b p = hsv_img.at<cv::Vec3b>(y, x);

      if (p[HUE] <= HUE_MIN || p[HUE] >= HUE_MAX) continue;
      if (p[SAT] <= SAT_MIN || p[SAT] >= SAT_MAX) continue;

      dst_img.at<uchar>(y, x) = MAX_VAL;
    }
  }

  // 5. 表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::waitKey();  // キー入力待ち (止める)

  return 0;
}
