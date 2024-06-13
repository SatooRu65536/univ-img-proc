#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./apple_grayscale.jpg"
#define FILTER_SIZE 3

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, 0);

  // 読み込み失敗の場合
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat median_img;

  // メディアンフィルタ
  cv::medianBlur(src_img, median_img, FILTER_SIZE);

  cv::imshow("input", src_img);
  cv::imshow("output", median_img);
  cv::imwrite("output.jpg", median_img);
  cv::waitKey(0);

  return 0;
}
