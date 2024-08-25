#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "./img/issue3.jpg"
#define TEMPLATE_IMG_FILE "./img/red_fish.jpg"
#define OUTPUT_IMG_FILE "issue3_k23075_result.jpg"

enum FishHueMap {
  RED = (unsigned char)179,
  YELLOW = (unsigned char)29,
};

/**
 * 色相を変換する
 * @param rgb_img 変換する画像
 * @param replace_hue 変換前の色相
 * @param hue 変換後の色相
 * @return cv::Mat 変換後の画像
 */
cv::Mat change_hue(cv::Mat rgb_img, FishHueMap replace_hue, FishHueMap hue) {
  cv::Mat hsv_img;
  // RGB から HSV に変換
  cv::cvtColor(rgb_img.clone(), hsv_img, cv::COLOR_BGR2HSV);

  // 色相の変換
  for (int y = 0; y < hsv_img.rows; y++) {
    for (int x = 0; x < hsv_img.cols; x++) {
      cv::Vec3b hsv = hsv_img.at<cv::Vec3b>(y, x);

      if (hsv[0] == replace_hue) {
        hsv[0] = hue;
        hsv_img.at<cv::Vec3b>(y, x) = hsv;
      }
    }
  }

  // HSV から RGB に変換
  cv::Mat result_img;
  cv::cvtColor(hsv_img, result_img, cv::COLOR_HSV2BGR);

  return result_img;
}

int main(int argc, const char* argv[]) {
  // 入力画像を読み込む
  cv::Mat src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
  cv::Mat template_red_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_COLOR);

  if (src_img.empty() || template_red_img.empty()) {
    printf("can not read image file\n");
    return (-1);
  }

  // 黄色い魚のテンプレ
  cv::Mat template_yellow_img = change_hue(template_red_img, RED, YELLOW);

  // 類似度マップの計算
  cv::Mat compare_img = cv::Mat(  //
      cv::Size(                   //
          src_img.rows - template_red_img.rows + 1,
          src_img.cols - template_red_img.cols + 1  //
          ),
      CV_32F, 1  //
  );
  cv::matchTemplate(src_img, template_yellow_img, compare_img,
                    cv::TM_SQDIFF_NORMED);

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
      cv::Point(min_loc.x + template_red_img.cols,
                min_loc.y + template_red_img.rows),  //
      cv::Scalar(0, 0, 255),                         //
      2                                              //
  );

  // 描画・保存
  cv::imshow("result", result_img);
  cv::imwrite(OUTPUT_IMG_FILE, result_img);

  // キー入力待ち
  cv::waitKey(0);

  return 0;
}
