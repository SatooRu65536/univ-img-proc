#include <iostream>
#include <opencv2/opencv.hpp>
#define TARGET_IMG_FILE "bg.jpg"

#define TEMPLATE_IMG_FILE "face.jpg"

int main(int argc, const char* argv[]) {
  cv::Mat src_img, template_img, compare_img, result_img;

  // 入力画像
  src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);

  if (src_img.empty()) {
    fprintf(stderr, "File is not opened.\n");

    return (-1);
  }

  // テンプレート画像
  template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_COLOR);

  // 類似度マップ (1チャンネル)
  compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1,
                                 src_img.cols - template_img.cols + 1),
                        CV_32F, 1);

  // 結果画像
  result_img = cv::Mat(src_img.size(), CV_8UC1);
  result_img = src_img.clone();  // 画像のコピー

  // ここまでが初期化 (前処理)
  //------------------------------------------------------------

  // テンプレートマッチング
  cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

  // 類似度マップの最小値最大値の計算
  double min_val, max_val;
  cv::Point min_loc, max_loc;
  cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

  // min_loc, max_loc を出力
  // fprintf(stdout, "min_loc: (%d, %d)\n", min_loc.x, min_loc.y);
  // fprintf(stdout, "max_loc: (%d, %d)\n", max_loc.x, max_loc.y);

  // 長方形の表示
  // cv::rectangle(
  //     result_img, min_loc,
  //     cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows),
  //     CV_RGB(255, 0, 0), 3);

  float s;  // 類似度マップはfloat型
  for (int y = 0; y < compare_img.rows; y++) {
    for (int x = 0; x < compare_img.cols; x++) {
      s = compare_img.at<float>(y, x);  // float型で取得
      if (s < 0.1) {                    // 閾値以下
        // 長方形の表示
        cv::rectangle(result_img, cv::Point(x, y),
                      cv::Point(x + template_img.cols, y + template_img.rows),
                      CV_RGB(255, 0, 0), 3);
        fprintf(stderr, "%d, %d\n", x, y);
      }
    }
  }

  // 探索画像の描画
  cv::imshow("input", src_img);           // 入力画像
  cv::imshow("template", template_img);   // テンプレート画像
  cv::imshow("result", result_img);       // 結果画像
  cv::imwrite("result.jpg", result_img);  // 結果画像の保存
  // キー入力待ち
  cv::waitKey(0);

  return 0;
}
