#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./kagoshima.jpg"
#define COLOR_MAX (256)  // 階調数

int main(int argc, const char* argv[]) {
  // ① 変数の宣言, ② 初期値の設定（Imin,Imax）
  unsigned char Imin = 255, Imax = 0;
  unsigned char Dmin = 0, Dmax = 255;

  // ③ 画像（グレースケール）の読込み
  cv::Mat src_img = cv::imread(FILE_NAME, 0);
  if (src_img.empty()) {  // 読み込み失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  // ④ 出力画像の領域確保
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  for (int y = 0; y < dst_img.rows; y++) {
    for (int x = 0; x < dst_img.cols; x++) {
      unsigned char s = src_img.at<unsigned char>(y, x);
      // ⑤ 入力画像輝度値の最小値、最大値の取得
      if (s < Imin) Imin = s;
      if (s > Imax) Imax = s;
    }
  }

  for (int y = 0; y < dst_img.rows; y++) {
    for (int x = 0; x < dst_img.cols; x++) {
      unsigned char s = src_img.at<unsigned char>(y, x);
      // ⑥ 線形変換（入力画像→出力画像）
      dst_img.at<unsigned char>(y, x) =
          (Dmax - Dmin) / (Imax - Imin) * (s - Imin) + Dmin;
    }
  }

  // ⑦ 表示
  cv::imshow("input", src_img);
  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
