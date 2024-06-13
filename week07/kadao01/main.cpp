#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME_1 "./issue_input1.jpg"
#define FILE_NAME_2 "./issue_input2.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img1 = cv::imread(FILE_NAME_1, 0);
  cv::Mat src_img2 = cv::imread(FILE_NAME_2, 0);

  // 読み込み失敗の場合
  if (src_img1.empty() || src_img2.empty()) {
    fprintf(stderr, "読み込み失敗\n");
    return (-1);
  }

  cv::Mat blur_img = cv::Mat(src_img1.size(), CV_8UC1);
  int filter_size = 3;

  // 最も最小となった差分のピクセル数
  int diff = src_img1.rows * src_img1.cols;
  // 最適なフィルターサイズ
  int filter_size_opt = 3;

  // フィルターサイズを変えながら差分を計算
  for (filter_size = 3; filter_size <= 9; filter_size += 2) {
    cv::GaussianBlur(src_img2, blur_img, cv::Size(filter_size, filter_size), 0);

    // 差分のあるピクセルサイズをカウント
    int diff_current = 0;
    for (int y = 0; y < src_img1.rows; y++) {
      for (int x = 0; x < src_img1.cols; x++) {
        double s1 = src_img1.at<uchar>(y, x);
        double s2 = blur_img.at<uchar>(y, x);

        if (abs(s1 - s2) > 0) diff_current++;
      }
    }

    if (diff_current > diff) continue;

    // 差分のピクセル数が最小の場合は更新
    diff = diff_current;
    filter_size_opt = filter_size;
  }

  printf("最適なフィルターサイズ: %d\n", filter_size_opt);
  // 最適なフィルターサイズでブラー処理
  cv::GaussianBlur(src_img2, blur_img,
                   cv::Size(filter_size_opt, filter_size_opt), 0);

  cv::Mat dst_img = cv::Mat(src_img1.size(), CV_8UC3);

  // 差分を黒色で2値化
  for (int y = 0; y < dst_img.rows; y++) {
    for (int x = 0; x < dst_img.cols; x++) {
      double s1 = blur_img.at<uchar>(y, x);
      double s2 = src_img1.at<uchar>(y, x);

      if (abs(s1 - s2) > 40) {
        dst_img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 255);
      } else {
        dst_img.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
      }
    }
  }

  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
