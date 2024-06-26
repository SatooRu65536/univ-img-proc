#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./a_img.jpg"
#define HIGHVAL (255)

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);

  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat bin_img, dst_img;

  // 二値化
  cv::threshold(src_img, bin_img, 100, HIGHVAL, cv::THRESH_BINARY);
  dst_img = bin_img.clone();

  // 膨超
  for (int i = 0; i < 10; i++) {
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 1);
    cv::imshow("膨超", dst_img);
    cv::waitKey();
  }

  // 収縮
  for (int i = 0; i < 10; i++) {
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 1);
    cv::imshow("膨超", dst_img);
    cv::waitKey();
  }

  // 順番を入れ替える

  dst_img = bin_img.clone();
  // 収縮
  for (int i = 0; i < 10; i++) {
    cv::erode(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 1);
    cv::imshow("膨超", dst_img);
    cv::waitKey();
  }

  // 膨超
  for (int i = 0; i < 10; i++) {
    cv::dilate(dst_img, dst_img, cv::Mat(), cv::Point(-1, -1), 1);
    cv::imshow("膨超", dst_img);
    cv::waitKey();
  }

  // cv::imshow("INPUT", src_img);
  // cv::imwrite("output.jpg", bin_img);
  // cv::waitKey();

  return 0;
}
