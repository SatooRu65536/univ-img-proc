#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./moon-is-kirei.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img = cv::imread(FILE_NAME, 0);

  // 読み込み失敗の場合
  if (src_img.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat dst_img_v = cv::Mat(src_img.size(), CV_8UC1);
  cv::Mat dst_img_h = cv::Mat(src_img.size(), CV_8UC1);
  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  double filter_h_v[3][3] = {
      {0, 0, 0},   //
      {-1, 0, 1},  //
      {0, 0, 0}    //
  };
  double filter_h_h[3][3] = {
      {0, -1, 0},  //
      {0, 0, 0},   //
      {0, 1, 0}    //
  };
  cv::Mat kernel_v = cv::Mat(3, 3, CV_64F, filter_h_v);
  cv::Mat kernel_h = cv::Mat(3, 3, CV_64F, filter_h_h);

  // フィルター処理
  cv::filter2D(src_img, dst_img_v, -1, kernel_v);
  cv::filter2D(src_img, dst_img_h, -1, kernel_h);

  cv::convertScaleAbs(dst_img_v, dst_img_v);
  // cv::convertScaleAbs(dst_img_h, dst_img_h);

  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      // 画素値の取得
      uchar s_v = dst_img_v.at<uchar>(y, x);
      uchar s_h = dst_img_h.at<uchar>(y, x);

      dst_img.at<uchar>(y, x) = sqrt(s_v * s_v + s_h * s_h);
    }
  }

  cv::convertScaleAbs(dst_img, dst_img);

  cv::imshow("output v", dst_img_v);
  cv::imshow("output h", dst_img_h);
  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
