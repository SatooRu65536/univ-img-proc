#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./apple_tree.jpg"
// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_OUTPUT2 "output2"

int main(int argc, const char* argv[]) {
  // 入力画像の読み込み
  cv::Mat src_img = cv::imread(FILE_NAME);
  if (src_img.empty()) {  // 読み込み失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }
  // 出力画像のメモリ確保
  cv::Mat gray_img = cv::Mat(src_img.size(), CV_8UC1);
  // グレースケール変換
  // 画像の走査
  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      // 画素値の取得
      cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
      uchar val = 0.114 * s[0]     // B
                  + 0.587 * s[1]   // G
                  + 0.299 * s[2];  // R
      gray_img.at<uchar>(y, x) = val;
    }
  }
  /* 後で記入 */
  cv::imshow(WINDOW_NAME_INPUT, src_img);    // 入力画像の表示
  cv::imshow(WINDOW_NAME_OUTPUT, gray_img);  // 出力画像の表示
  cv::waitKey();                             // キー入力待ち (止める)
  return 0;
}
