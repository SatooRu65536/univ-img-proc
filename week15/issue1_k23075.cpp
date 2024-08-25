#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "./img/issue1.jpg"
#define TEMPLATE_IMG_FILE "./img/red_fish.jpg"
#define OUTPUT_IMG_FILE "issue1_k23075_result.jpg"

int main(int argc, const char* argv[]) {
  // 入力画像を読み込む
  cv::Mat src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
  cv::Mat template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_COLOR);

  if (src_img.empty() || template_img.empty()) {
    printf("can not read image file\n");
    return (-1);
  }

  // 類似度マップの計算
  cv::Mat compare_img = cv::Mat(  //
      cv::Size(                   //
          src_img.rows - template_img.rows + 1,
          src_img.cols - template_img.cols + 1  //
          ),
      CV_32F, 1  //
  );
  cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

  // 類似度マップの最小値最大値の計算
  double min_val, max_val;
  cv::Point min_loc, max_loc;
  cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

  // 出力画像の作成
  cv::Mat result_img = src_img.clone();

  // 四角で囲む
  cv::rectangle(                        //
      result_img,                       //
      cv::Point(min_loc.x, min_loc.y),  //
      cv::Point(min_loc.x + template_img.cols,
                min_loc.y + template_img.rows),  //
      cv::Scalar(0, 0, 255),                     //
      2                                          //
  );

  // 描画・保存
  cv::imshow("result", result_img);
  cv::imwrite(OUTPUT_IMG_FILE, result_img);

  // キー入力待ち
  cv::waitKey(0);

  return 0;
}
