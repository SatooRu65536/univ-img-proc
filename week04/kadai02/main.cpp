#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./image2.jpg"
#define COLOR_MAX (256)

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, 0);
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  int pixels_count = 0;
  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      unsigned char s = src_img.at<unsigned char>(y, x);
      if (s < 121) {
        pixels_count++;
      }
    }
  }

  printf("%d\n", pixels_count);

  return 0;
}
