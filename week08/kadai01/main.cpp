#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./ptile.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define HIGHVAL (255)
#define HIST_SIZE (256)

int main(int argc, const char* argv[]) {
  double percent = 4.0 / (4.0 + 1.0);

  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_GRAYSCALE);
  if (src_img.empty()) {
    fprintf(stderr, "File is not opened.\n");
    return -1;
  }

  // ヒストグラムの生成
  int hist[HIST_SIZE] = {0};
  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      int pixel_value = src_img.at<uchar>(y, x);
      hist[pixel_value]++;
    }
  }

  // 全体面積のp%から該当の面積を取得
  int total_pixels = src_img.rows * src_img.cols;
  int target_area = total_pixels * percent;

  // ヒストグラムを使用して閾値を求める
  int sum = 0;
  int threshold = 0;
  for (int i = 0; i < HIST_SIZE; i++) {
    sum += hist[i];
    if (sum >= target_area) {
      threshold = i;
      break;
    }
  }
  printf("閾値: %d\n", threshold);

  // 二値化
  cv::Mat result_img;
  cv::threshold(src_img, result_img, threshold, HIGHVAL, cv::THRESH_BINARY);

  // 結果の表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_OUTPUT, result_img);
  cv::imwrite("output.jpg", result_img);
  cv::waitKey();

  return 0;
}
