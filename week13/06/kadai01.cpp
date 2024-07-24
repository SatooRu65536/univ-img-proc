#include <cstdio>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE_PATH "./ham.jpg"

int main() {
  // カラー画像を読み込み
  cv::Mat color_image = cv::imread(INPUT_IMAGE_PATH);
  if (color_image.empty()) {
    fprintf(stderr, "Error: could not load image %s\n", INPUT_IMAGE_PATH);
    return -1;
  }

  // グレースケールに変換
  cv::Mat gray_image;
  cv::cvtColor(color_image, gray_image, cv::COLOR_BGR2GRAY);

  // ガウシアンフィルタを適用
  cv::Mat gaussian_blurred;
  int kernel_size = 5;  // フィルタサイズは任意、ここでは5x5を使用
  cv::GaussianBlur(gray_image, gaussian_blurred,
                   cv::Size(kernel_size, kernel_size), 0);

  // ソーベルフィルタ(縦)を適用
  cv::Mat sobel_image;
  cv::Sobel(gaussian_blurred, sobel_image, CV_64F, 1, 0, 3);

  // ソーベルフィルタの結果を絶対値にし、8ビットに変換してスケーリング
  cv::Mat abs_sobel_image;
  cv::convertScaleAbs(sobel_image, abs_sobel_image);

  // 表示
  cv::imshow("Original Image", color_image);
  cv::imshow("Gaussian Blurred Image", gaussian_blurred);
  cv::imshow("Sobel Edge Image", abs_sobel_image);

  cv::waitKey(0);
  return 0;
}
