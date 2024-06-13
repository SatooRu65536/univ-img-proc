#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME_1 "./input1.jpg"
#define FILE_NAME_2 "./input2.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img1 = cv::imread(FILE_NAME_1, 0);
  cv::Mat src_img2 = cv::imread(FILE_NAME_2, 0);

  // 読み込み失敗の場合
  if (src_img1.empty() || src_img2.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat diff_img = cv::Mat(src_img1.size(), CV_8UC1);
  cv::Mat dst_img = cv::Mat(src_img1.size(), CV_8UC1);

  for (int y = 0; y < diff_img.rows; y++) {
    for (int x = 0; x < diff_img.cols; x++) {
      double s1 = src_img1.at<uchar>(y, x);
      double s2 = src_img2.at<uchar>(y, x);

      int s_res = abs(s1 - s2);

      diff_img.at<uchar>(y, x) = (uchar)s_res;

      if (s_res < 20)
        dst_img.at<uchar>(y, x) = 0;
      else
        dst_img.at<uchar>(y, x) = 255;
    }
  }

  cv::imshow("diff output", diff_img);
  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
