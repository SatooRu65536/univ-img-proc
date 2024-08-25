#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "./img/issue6.jpg"
#define TEMPLATE_IMG_FILE "./img/red_fish.jpg"

#define RED cv::Vec3b(179, 233, 231)
#define YELLOW cv::Vec3b(29, 195, 238)
#define LIGHT_BLUE cv::Vec3b(92, 126, 205)
#define BLUE cv::Vec3b(113, 172, 159)
#define PURPLE cv::Vec3b(154, 122, 169)
#define GREEN cv::Vec3b(50, 167, 185)

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
int count(cv::Mat src_img, cv::Mat template_img, float th) {
  cv::Mat tmp_img = src_img.clone();
  cv::Mat compare_img = cv::Mat(cv::Size(src_img.rows - template_img.rows + 1,
                                         src_img.cols - template_img.cols + 1),
                                CV_32F, 1);

  int count = 0;
  while (1) {
    // 類似度マップ作成
    cv::matchTemplate(tmp_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);
    // 最小値とその場所を求める
    double min_val, max_val;
    cv::Point min_loc, max_loc;
    cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

    if (min_val > th) break;

    // 個数を1つ増加
    count++;

    // 一時画像からその領域を削除（塗りつぶす）
    cv::rectangle(
        tmp_img, min_loc,
        cv::Point(min_loc.x + template_img.cols, min_loc.y + template_img.rows),
        CV_RGB(0, 0, 0), -1);
  };

  return count;
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
  int count_red = count(src_img, template_img, 0.2);
  printf("%d: %d\n", RED[0], count_red);

  // 緑色
  cv::Mat green_template_img = change_hsv_color(template_img, RED, GREEN);
  int count_green = count(src_img, green_template_img, 0.15);
  printf("%d: %d\n", GREEN[0], count_green);

  // 水色
  cv::Mat light_blue_template_img =
      change_hsv_color(template_img, RED, LIGHT_BLUE);
  int count_light_blue = count(src_img, light_blue_template_img, 0.15);
  printf("%d: %d\n", LIGHT_BLUE[0], count_light_blue);

  // 青色
  cv::Mat blue_template_img = change_hsv_color(template_img, RED, BLUE);
  int count_blue = count(src_img, blue_template_img, 0.15);
  printf("%d: %d\n", BLUE[0], count_blue);

  // 黄色
  cv::Mat yellow_template_img = change_hsv_color(template_img, RED, YELLOW);
  int count_yellow = count(src_img, yellow_template_img, 0.1);
  printf("%d: %d\n", YELLOW[0], count_yellow);

  // 紫色
  cv::Mat purple_template_img = change_hsv_color(template_img, RED, PURPLE);
  int count_purple = count(src_img, purple_template_img, 0.1);
  printf("%d: %d\n", PURPLE[0], count_purple);

  int fish_sum = count_red + count_yellow + count_light_blue + count_blue +
                 count_purple + count_green;
  printf("合計: %d\n", fish_sum);

  return 0;
}
