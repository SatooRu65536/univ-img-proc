#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./red_rectangle.jpg"
#define COLOR_MAX (256)  // 階調数

int main(int argc, const char* argv[]) {
  // ② 画像をグレースケールで入力
  cv::Mat src_img = cv::imread(FILE_NAME, 0);
  if (src_img.empty()) {  // 読み込み失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  // ① 変数の宣言
  int hist[COLOR_MAX];
  // ③ ヒストグラム用配列の初期化
  for (int i = 0; i < COLOR_MAX; i++) hist[i] = 0;

  // 出力画像のメモリ確保
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  // ④ ヒストグラムの生成
  for (int y = 0; y < dst_img.rows; y++) {
    for (int x = 0; x < dst_img.cols; x++) {
      unsigned char s = src_img.at<unsigned char>(y, x);
      hist[(int)s]++;
    }
  }

  // ⑤ 出力
  for (int i = 0; i < COLOR_MAX; i++) {
    printf("%d,%d\n", i, hist[i]);
  }

  return 0;
}
