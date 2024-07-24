#include <cstdio>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE "./gazoDora.jpg"
#define TEMPLATE_IMAGE "red.jpg"

int main() {
  // 画像の読み込み
  cv::Mat input_image = cv::imread(INPUT_IMAGE, cv::IMREAD_GRAYSCALE);
  cv::Mat template_image = cv::imread(TEMPLATE_IMAGE, cv::IMREAD_GRAYSCALE);

  // 画像が正しく読み込まれたか確認
  if (input_image.empty()) {
    fprintf(stderr, "Error: Cannot load input image\n");
    return -1;
  }
  if (template_image.empty()) {
    fprintf(stderr, "Error: Cannot load template image\n");
    return -1;
  }

  // 類似度マップのサイズを計算
  int result_cols = input_image.cols - template_image.cols + 1;
  int result_rows = input_image.rows - template_image.rows + 1;
  cv::Mat result(result_rows, result_cols, CV_32FC1);

  // テンプレートマッチングを実行（TM_SQDIFF_NORMED）
  cv::matchTemplate(input_image, template_image, result, cv::TM_SQDIFF_NORMED);

  // 類似度マップを表示
  cv::imshow("Result", result);
  cv::waitKey(0);

  return 0;
}
