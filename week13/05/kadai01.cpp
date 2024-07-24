#include <cstdio>
#include <opencv2/opencv.hpp>

#define FILTER_SIZE 3
#define INPUT_IMAGE_PATH "./apple_grayscale.jpg"

int main() {
  // 画像の読み込み
  cv::Mat input_image = cv::imread(INPUT_IMAGE_PATH, cv::IMREAD_GRAYSCALE);
  if (input_image.empty()) {
    fprintf(stderr, "Failed to load image: %s\n", INPUT_IMAGE_PATH);
    return -1;
  }

  // フィルタサイズが偶数の場合は処理を終了
  if (FILTER_SIZE % 2 == 0) {
    fprintf(stderr, "Filter size %d is even. Processing is not performed.\n",
            FILTER_SIZE);
    return 0;
  }

  // 平均化フィルタのカーネル作成
  cv::Mat filter_kernel = cv::Mat::ones(FILTER_SIZE, FILTER_SIZE, CV_32F) /
                          (float)(FILTER_SIZE * FILTER_SIZE);

  // フィルタ適用
  cv::Mat output_image;
  cv::filter2D(input_image, output_image, -1, filter_kernel);

  // 入力画像とフィルタ後の画像を表示
  cv::imshow("Input Image", input_image);
  cv::imshow("Filtered Image", output_image);

  // キー入力待ち
  cv::waitKey(0);

  return 0;
}
