#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "fruit_image.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
#define WINDOW_NAME_BIN "output bin"

#define H_MIN (12)
#define H_MAX (24)
#define S_MIN (195)
#define S_MAX (255)
#define V_MIN (180)
#define V_MAX (255)

#define WHITE_PIXEL (255)
#define BLACK_PIXEL (0)

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
  if (src_img.empty()) {
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }

  cv::Mat bin_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
  cv::Mat dst_img = src_img.clone();
  cv::Mat hsv_img;
  cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

  for (int y = 0; y < hsv_img.rows; y++) {
    for (int x = 0; x < hsv_img.cols; x++) {
      cv::Vec3b p = hsv_img.at<cv::Vec3b>(y, x);
      int h = p[0];
      int s = p[1];
      int v = p[2];

      if (h < H_MIN || h > H_MAX) continue;
      if (s < S_MIN || s > S_MAX) continue;
      if (v < V_MIN || v > V_MAX) continue;

      bin_img.at<uchar>(y, x) = WHITE_PIXEL;
      dst_img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 255, 255);
    }
  }

  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::imshow(WINDOW_NAME_BIN, bin_img);
  cv::waitKey();

  return 0;
}
