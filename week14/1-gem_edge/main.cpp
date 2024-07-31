#include <opencv2/opencv.hpp>
#define FILE_NAME "gem1.jpg"

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_GRAYSCALE "grayscale"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* argv[]) {
  // 1. 入力画像をカラーで入力
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);

  if (src_img.empty()) {
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }

  // 2. グレースケール画像
  cv::Mat gray_img;
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 3. エッジ検出（cannyオペレータ)
  cv::Mat dst_img;
  cv::Canny(gray_img, dst_img, 100, 200);

  // 4. 表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_GRAYSCALE, gray_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::waitKey();  // キー入力待ち (止める)

  return 0;
}
