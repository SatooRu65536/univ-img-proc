#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "gazoDora.jpg"
#define TEMPLATE_IMG_FILE "red.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img;

  // 入力画像
  src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_GRAYSCALE);

  if (src_img.empty()) {
    fprintf(stderr, "File is not opened.\n");
    return (-1);
  }

  // テンプレート画像
  cv::Mat template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_GRAYSCALE);

  // 類似度マップ (1チャンネル)
  cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1,
                                         src_img.cols - template_img.cols + 1),
                                CV_32F, 1);

  // テンプレートマッチング
  cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

  // 探索画像の描画
  cv::imshow("input", src_img);            // 入力画像
  cv::imshow("template", template_img);    // テンプレート画像
  cv::imshow("compare", compare_img);      // 結果画像
  cv::imwrite("result.jpg", compare_img);  // 結果画像の保存
  // キー入力待ち
  cv::waitKey(0);

  return 0;
}
