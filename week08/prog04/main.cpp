#include <iostream>
// OpenCV用のヘッダファイル
#include <opencv2/opencv.hpp>
// 画像ファイル (サイズは小さめが良い)
#define FILE_NAME "./canvas.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define TH (127)
#define HIGHVAL (255)

int main(int argc, const char* argv[]) {
  // 画像の入力
  // 　グレースケールで読み込む
  cv::Mat src_img1 = cv::imread(FILE_NAME, 0);  // 画像の読み込み
  if (src_img1.empty()) {                       // 入力失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC1);
  int val = cv::threshold(src_img1, result_img, 0, HIGHVAL,
                          cv::THRESH_BINARY | cv::THRESH_OTSU);
  printf("閾値 = %d\n", val);

  // 画像の出力
  cv::imshow(WINDOW_NAME_OUTPUT, result_img);  // 出力画像の表示
  cv::waitKey();                               // キー入力待ち

  return 0;
}
