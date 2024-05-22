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

  cv::Mat dst_img = cv::Mat(src_img.size(), CV_8UC1);

  if (FILTER_SIZE % 2 == 0) {
    printf("フィルターサイズは奇数である必要があります\n");
    return (-1);
  }

  double filter_h[FILTER_SIZE][FILTER_SIZE];
  for (int i = 0; i < FILTER_SIZE; i++) {
    for (int j = 0; j < FILTER_SIZE; j++) {
      filter_h[i][j] = 1.0 / (FILTER_SIZE * FILTER_SIZE);
    }
  }

  cv::Mat kernel = cv::Mat(FILTER_SIZE, FILTER_SIZE, CV_32F, filter_h);

  // 正規化
  cv::normalize(kernel, kernel, 1.0, 0.0, cv::NORM_L1);

  // フィルター処理
  cv::filter2D(src_img, dst_img, -1, kernel);

  cv::imshow("output", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey(0);

  return 0;
}
