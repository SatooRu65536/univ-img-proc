#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "./img/issue4.jpg"
#define TEMPLATE_IMG_FILE "./img/red_fish.jpg"
#define OUTPUT_IMG_FILE "issue4_k23075_result.jpg"

#define RED cv::Vec3b(179, 233, 231)
#define YELLOW cv::Vec3b(29, 195, 238)

/**
 * 大体同じ色かどうかを判定する
 * @param target 比較対象
 * @param compare 比較する色
 * @param th 許容誤差
 */
bool is_same_color(cv::Vec3b target, cv::Vec3b compare, int th) {
  for (int i = 0; i < 3; i++) {
    if (abs(target[i] - compare[i]) > th) return false;
  }
  return true;
}

/**
 * 色相を変換する
 * @param rgb_img 変換する画像
 * @param target_hsv 変換前の色相
 * @param replace_hsv 変換後の色相
 * @return cv::Mat 変換後の画像
 */
cv::Mat change_hsv_color(cv::Mat rgb_img, cv::Vec3b target_hsv,
                         cv::Vec3b replace_hsv) {
  cv::Mat hsv_img;
  // RGB から HSV に変換
  cv::cvtColor(rgb_img.clone(), hsv_img, cv::COLOR_BGR2HSV);

  // 色相の変換
  for (int y = 0; y < hsv_img.rows; y++) {
    for (int x = 0; x < hsv_img.cols; x++) {
      cv::Vec3b hsv = hsv_img.at<cv::Vec3b>(y, x);

      if (is_same_color(hsv, target_hsv, 5)) {
        hsv_img.at<cv::Vec3b>(y, x) = replace_hsv;
      }
    }
  }

  // HSV から RGB に変換
  cv::Mat result_img;
  cv::cvtColor(hsv_img, result_img, cv::COLOR_HSV2BGR);

  return result_img;
}

/**
 * 長方形を描画する
 *
 * @param src_img 入力画像
 * @param template_img テンプレート画像
 * @param th 類似度の閾値
 */
void draw_rect(cv::Mat img, cv::Mat template_img, float th) {
  cv::Mat tmp_img = img.clone();
  cv::Mat compare_img = cv::Mat(cv::Size(img.rows - template_img.rows + 1,
                                         img.cols - template_img.cols + 1),
                                CV_32F, 1);

  while (1) {
    // 類似度マップ作成
    cv::matchTemplate(tmp_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
    // 最小値とその場所を求める
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

    if (min_val > th) break;

    // 長方形で囲む
    cv::rectangle(
        img, min_loc,
        cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows),
        CV_RGB(255, 0, 0), 2);

    // 一時画像からその領域を削除（塗りつぶす）
    cv::rectangle(
        tmp_img, min_loc,
        cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows),
        CV_RGB(0, 0, 0), -1);
  };
}

int main(int argc, const char* argv[]) {
  // 入力画像を読み込む
  cv::Mat src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);
  cv::Mat template_img = cv::imread(TEMPLATE_IMG_FILE, cv::IMREAD_COLOR);

  if (src_img.empty() || template_img.empty()) {
    printf("can not read image file\n");
    return (-1);
  }

  // 赤色
  draw_rect(src_img, template_img, 0.2);

  // 黄色
  cv::Mat yellow_template_img = change_hsv_color(template_img, RED, YELLOW);
  draw_rect(src_img, yellow_template_img, 0.1);

  // 描画
  cv::imshow("result", src_img);
  cv::imwrite(OUTPUT_IMG_FILE, src_img);
  cv::waitKey(0);

  return 0;
}
