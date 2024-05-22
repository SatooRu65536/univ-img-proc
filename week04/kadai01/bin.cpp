#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME_INPUT "./image1.jpg"

int main(int argc, const char* argv[]) {
  int x = 0, y = 0;

  cv::Mat src_img;

  src_img = cv::imread(FILE_NAME_INPUT, 0);
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);
  for (y = 0; y < src_img.rows; y++) {
    for (x = 0; x < src_img.cols; x++) {
      unsigned char s = src_img.at<unsigned char>(y, x);
      if (s < 125) dst_img.at<unsigned char>(y, x) = 255;
    }
  }

  cv::imshow(FILE_NAME_INPUT, src_img);
  cv::imshow("OUTPUT", dst_img);
  cv::imwrite("output.jpeg", dst_img);
  cv::waitKey();

  return 0;
}
