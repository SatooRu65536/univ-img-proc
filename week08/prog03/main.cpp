#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./canvas.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define TH (127)
#define HIGHVAL (255)

int main(int argc, const char* argv[]) {
  cv::Mat src_img1 = cv::imread(FILE_NAME);
  if (src_img1.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat result_img = cv::Mat(src_img1.size(), CV_8UC3);

  cv::threshold(src_img1, result_img, TH, HIGHVAL, cv::THRESH_BINARY_INV);

  cv::imshow(WINDOW_NAME_OUTPUT, result_img);
  cv::waitKey();

  return 0;
}
