#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "fruit_image.jpg"

// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define R_MIN (100)        // Rのしきい値
#define G_MIN (30)         // Gのしきい値
#define G_MAX (100)        // Gのしきい値
#define B_MIN (50)         // Bのしきい値
#define B_MAX (100)        // Bのしきい値
#define WHITE_PIXEL (255)  // 出力画像の値（白）

int main(int argc, const char* argv[]) {
  // 変数の宣言
  int x, y;     // 走査用
  cv::Vec3b p;  // 色値

  // 画像の宣言 (入力画像，出力画像)
  cv::Mat src_img, dst_img;

  // 1. カラー画像の入力
  src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }

  // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
  dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

  // 3. しきい値処理
  for (y = 0; y < src_img.rows; y++) {
    for (x = 0; x < src_img.cols; x++) {
      // 色値の取得
      p = src_img.at<cv::Vec3b>(y, x);

      // BGRの値を取得
      int b = p[0];
      int g = p[1];
      int r = p[2];

      // しきい値処理
      if (r > R_MIN && g > G_MIN && g < G_MAX && b > B_MIN && b < B_MAX) {
        dst_img.at<uchar>(y, x) = WHITE_PIXEL;
      }
    }
  }

  // 4. 表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);   // 入力画像の表示
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);  // 出力画像の表示
  cv::waitKey();                            // キー入力待ち (止める)

  return 0;
}
