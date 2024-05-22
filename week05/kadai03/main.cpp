#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./yakisoba.jpg"
#define FILTER_SIZE 9

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, 0);

  // 読み込み失敗の場合
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  if (FILTER_SIZE % 2 == 0) {
    printf("フィルターサイズは奇数である必要があります\n");
    return (-1);
  }

  double filter = 1.0 / (FILTER_SIZE * FILTER_SIZE);

  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      double sum = 0.0;

      for (int dx = -FILTER_SIZE / 2; dx <= FILTER_SIZE / 2; dx++) {
        for (int dy = -FILTER_SIZE / 2; dy <= FILTER_SIZE / 2; dy++) {
          int sx = x + dx;
          int sy = y + dy;

          // 画像の端の場合
          if (sx < 0 || sx >= src_img.cols) continue;
          if (sy < 0 || sy >= src_img.rows) continue;

          sum += src_img.at<uchar>(sy, sx) * filter;
        }
      }

      dst_img.at<uchar>(y, x) = (uchar)sum;
    }
  }

  cv::imshow("output", dst_img);
  cv::waitKey(0);

  return 0;
}
