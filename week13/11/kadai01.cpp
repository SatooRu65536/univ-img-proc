#include <cstdio>
#include <opencv2/opencv.hpp>

// 入力画像のパスをマクロで定義
#define INPUT_IMAGE_PATH "./hand.jpg"

int main() {
  // 画像の読み込み
  cv::Mat image = cv::imread(INPUT_IMAGE_PATH);
  if (image.empty()) {
    fprintf(stderr, "Error: Could not open or find the image.\n");
    return -1;
  }

  // 画像をHSVに変換
  cv::Mat hsv_image;
  cv::cvtColor(image, hsv_image, cv::COLOR_BGR2HSV);

  // 赤色の範囲を定義
  int low_h1 = 0, high_h1 = 10;     // 0-10度
  int low_h2 = 170, high_h2 = 180;  // 170-180度
  int low_s = 50, high_s = 255;     // 彩度の範囲
  int low_v = 50, high_v = 255;     // 明度の範囲

  // 赤色領域を検出して色相値を15に変更
  for (int y = 0; y < hsv_image.rows; y++) {
    for (int x = 0; x < hsv_image.cols; x++) {
      cv::Vec3b pixel = hsv_image.at<cv::Vec3b>(y, x);
      int h = pixel[0], s = pixel[1], v = pixel[2];

      // 色相値の範囲をチェック
      if (!((h >= low_h1 && h <= high_h1) || (h >= low_h2 && h <= high_h2))) {
        continue;
      }

      // 彩度の範囲をチェック
      if (s < low_s || s > high_s) {
        continue;
      }

      // 明度の範囲をチェック
      if (v < low_v || v > high_v) {
        continue;
      }

      // 赤色だったら色相値を15に変更
      hsv_image.at<cv::Vec3b>(y, x)[0] = 15;
    }
  }

  // 画像をBGRに戻す
  cv::Mat result_image;
  cv::cvtColor(hsv_image, result_image, cv::COLOR_HSV2BGR);

  // 結果画像を表示
  cv::imshow("Original Image", image);
  cv::imshow("Processed Image", result_image);

  // 任意のキーが押されるまで待つ
  cv::waitKey(0);

  return 0;
}
