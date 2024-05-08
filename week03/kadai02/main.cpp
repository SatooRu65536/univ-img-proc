#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "./grayscale.jpg"
// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define COLOR_NUM (256)  // 階調数
#define IMAX 255

cv::Vec3b gray2color(uchar gray) {
  uchar red = 0;
  uchar green = gray < 64 ? gray * 4 : 255;
  uchar blue = 255;

  if (gray > 64) {
    int blueTmp = 255 - (gray - 64) * 4;
    blue = blueTmp < 0 ? 0 : blueTmp;
  }

  if (gray > 128) {
    int redTmp = (gray - 128) * 4;
    red = redTmp > 255 ? 255 : redTmp;
  }

  if (gray > 192) {
    green = 255 - (gray - 192) * 4;
  }

  return cv::Vec3b(blue, green, red);
}

int main(int argc, const char* argv[]) {
  // 入力画像の読み込み (グレースケール入力)
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
  if (src_img.empty()) {  // 読み込み失敗の場合
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }
  // 出力画像のメモリ確保
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);

  cv::Vec3b lut[COLOR_NUM];

  for (int i = 0; i < COLOR_NUM; i++) {
    lut[i] = gray2color(i);
  }

  // 画像の走査
  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      // 画素値の取得
      uchar s = src_img.at<uchar>(y, x);
      dst_img.at<cv::Vec3b>(y, x) = lut[s];
    }
  }

  cv::imshow(WINDOW_NAME_INPUT, src_img);   // 入力画像の表示
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);  // 出力画像の表示
  cv::imwrite("output.jpg", dst_img);       // 出力画像の保存
  cv::waitKey();                            // キー入力待ち (止める)

  return 0;
}
