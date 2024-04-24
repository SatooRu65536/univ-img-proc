#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME_INPUT "./aquarium.jpg"
#define FILE_NAME_OUTPUT "./output.jpg"
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char *argv[]) {
  int x, y;

  cv::Mat src_img = cv::imread(FILE_NAME_INPUT);
  if (src_img.empty()) return (-1);

  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC3);

  for (y = 0; y < src_img.rows; y++) {
    for (x = 0; x < src_img.cols; x++) {
      cv::Vec3b s = src_img.at<cv::Vec3b>(y, x);
      if (y > (src_img.rows / 2)) {
        s[0] = 0;
        s[1] = 0;
      }
      dst_img.at<cv::Vec3b>(y, x) = s;
    }
  }

  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::imwrite(FILE_NAME_OUTPUT, dst_img);
  cv::waitKey();

  return 0;
}
