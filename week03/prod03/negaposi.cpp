#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./fruit_image.jpg"
// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define IMAX 255


int main(int argc, const char* argv[]) {
  // 入力画像の読み込み (グレースケール入力)
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
  if (src_img.empty()) {  // 読み込み失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }
  // 出力画像のメモリ確保
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  // 濃淡反転
  dst_img = IMAX - src_img;

  cv::imshow(WINDOW_NAME_INPUT, src_img);   // 入力画像の表示
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);  // 出力画像の表示
  cv::waitKey();                            // キー入力待ち (止める)

  return 0;
}
