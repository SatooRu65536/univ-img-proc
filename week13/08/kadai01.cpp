#include <iostream>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE "./ptile.jpg"

int main() {
  // 入力画像をグレースケールで読み込む
  cv::Mat gray_image = cv::imread(INPUT_IMAGE, cv::IMREAD_GRAYSCALE);
  if (gray_image.empty()) {
    fprintf(stderr, "Could not open or find the image\n");
    return -1;
  }

  // ヒストグラムの計算
  int hist_size = 256;
  float range[] = {0, 256};
  const float* hist_range = {range};
  cv::Mat hist;
  cv::calcHist(&gray_image, 1, 0, cv::Mat(), hist, 1, &hist_size, &hist_range);

  // ヒストグラムの累積度数を計算
  std::vector<float> cumulative_hist(hist_size, 0);
  cumulative_hist[0] = hist.at<float>(0);
  for (int i = 1; i < hist_size; i++) {
    cumulative_hist[i] = cumulative_hist[i - 1] + hist.at<float>(i);
  }

  // 全ピクセル数と閾値の計算
  double total_pixels = gray_image.rows * gray_image.cols;
  double threshold_area = total_pixels * (4.0 / (4.0 + 1.0));

  // 閾値を見つける
  int threshold = 0;
  for (int i = 0; i < hist_size; i++) {
    if (cumulative_hist[i] >= threshold_area) {
      threshold = i;
      break;
    }
  }

  // 二値化
  cv::Mat binary_image;
  cv::threshold(gray_image, binary_image, threshold, 255, cv::THRESH_BINARY);

  // 二値化された画像を表示
  cv::imshow("Binary Image", binary_image);
  cv::waitKey(0);

  return 0;
}
