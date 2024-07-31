#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "gem1.jpg"
#define TEMPLATE "gem-green.jpg"

#define TH (0.15)

// ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

int main(int argc, const char* argv[]) {
  // 1. 画像を入力
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }

  // 2. テンプレート画像を入力
  cv::Mat template_img = cv::imread(TEMPLATE, cv::IMREAD_COLOR);
  if (template_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "Cannot read image file: %s.\n", TEMPLATE);
    return (-1);
  }

  // 3. 類似度マップを準備
  cv::Mat compare_img = cv::Mat(                 //
      cv::Size(                                  //
          src_img.rows - template_img.rows + 1,  //
          src_img.cols - template_img.cols + 1   //
          ),
      CV_32F,  //
      1        //
  );

  // 4. 一時画像と出力画像を用意
  cv::Mat tmp_img = src_img.clone();  // 入力画像をコピー
  cv::Mat dst_img = src_img.clone();  // 入力画像をコピー

  // 5. テンプレートマッチング
  int count = 0;  // 個数
  while (1) {
    // 類似度マップ作成
    cv::matchTemplate(tmp_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
    cv::imshow("comp", compare_img);
    cv::waitKey(1);

    // 最小値とその場所を求める
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

    if (min_val > TH) break;

    // 個数を1つ増加
    count++;

    // 出力画像に描画
    cv::rectangle(
        dst_img, min_loc,
        cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows),
        CV_RGB(255, 0, 0), 3);

    // 一時画像からその領域を削除（塗りつぶす）
    cv::rectangle(
        tmp_img, min_loc,
        cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows),
        CV_RGB(0, 0, 0), -1);
  };

  // 6. 個数を出力
  std::cout << "Green gem = " << count << std::endl;

  // 7. 表示
  cv::imshow(WINDOW_NAME_INPUT, src_img);
  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::waitKey();  // キー入力待ち (止める)

  return 0;
}
