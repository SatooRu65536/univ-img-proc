#include <iostream>
#include <opencv2/opencv.hpp>

#define TARGET_IMG_FILE "gazoDora.jpg"
#define TEMPLATE_IMG_FILE_RED "red.jpg"
#define TEMPLATE_IMG_FILE_STAR "star.jpg"
#define TEMPLATE_IMG_FILE_YELLOW "yellow.jpg"
#define TEMPLATE_IMG_FILE_GREEN "green.jpg"

std::vector<cv::Point> find_template(  //
    cv::Mat src_img,                   //
    cv::Mat template_img,              //
    double th                          //
) {
  cv::Mat compare_img = cv::Mat(  //
      cv::Size(                   //
          src_img.rows - template_img.rows + 1,
          src_img.cols - template_img.cols + 1  //
          ),
      CV_32F, 1  //
  );

  // 結果画像
  cv::Mat result_img = cv::Mat(src_img.size(), CV_8UC1);
  result_img = src_img.clone();  // 画像のコピー

  // テンプレートマッチング
  cv::matchTemplate(src_img, template_img, compare_img, cv::TM_SQDIFF_NORMED);

  // 類似度マップの最小値最大値の計算
  double min_val, max_val;
  cv::Point min_loc, max_loc;
  cv::minMaxLoc(compare_img, &min_val, &max_val, &min_loc, &max_loc);

  std::vector<cv::Point> points;

  float s;
  for (int y = 0; y < compare_img.rows; y++) {
    for (int x = 0; x < compare_img.cols; x++) {
      s = compare_img.at<float>(y, x);  // float型で取得
      if (s <= th) {                    // 閾値以下
        points.push_back(cv::Point(x, y));
      }
    }
  }

  return points;
}

int main(int argc, const char* argv[]) {
  cv::Mat src_img, compare_img;

  // 入力画像
  src_img = cv::imread(TARGET_IMG_FILE, cv::IMREAD_COLOR);

  if (src_img.empty()) {
    fprintf(stderr, "File is not opened.\n");

    return (-1);
  }

  // テンプレート画像
  cv::Mat template_img_red =
      cv::imread(TEMPLATE_IMG_FILE_RED, cv::IMREAD_COLOR);
  cv::Mat template_img_star =
      cv::imread(TEMPLATE_IMG_FILE_STAR, cv::IMREAD_COLOR);
  cv::Mat template_img_yellow =
      cv::imread(TEMPLATE_IMG_FILE_YELLOW, cv::IMREAD_COLOR);
  cv::Mat template_img_green =
      cv::imread(TEMPLATE_IMG_FILE_GREEN, cv::IMREAD_COLOR);

  std::vector<cv::Point> points_red =
      find_template(src_img, template_img_red, 0.05);
  std::vector<cv::Point> points_star =
      find_template(src_img, template_img_star, 0.05);
  std::vector<cv::Point> points_yellow =
      find_template(src_img, template_img_yellow, 0.05);
  std::vector<cv::Point> points_green =
      find_template(src_img, template_img_green, 0.05);

  cv::Mat result_img = cv::Mat(src_img.size(), CV_8UC3);
  result_img = src_img.clone();  // 画像のコピー

  for (cv::Point point : points_red) {
    cv::rectangle(
        result_img, point,
        cv::Point(point.x + template_img_red.cols, point.y + template_img_red.rows),
        CV_RGB(255, 0, 0), 3);
  }
  for (cv::Point point : points_star) {
    cv::rectangle(
        result_img, point,
        cv::Point(point.x + template_img_star.cols, point.y + template_img_star.rows),
        CV_RGB(255, 0, 255), 3);
  }
  for (cv::Point point : points_yellow) {
    cv::rectangle(
        result_img, point,
        cv::Point(point.x + template_img_yellow.cols, point.y + template_img_yellow.rows),
        CV_RGB(255, 255, 0), 3);
  }
  for (cv::Point point : points_green) {
    cv::rectangle(
        result_img, point,
        cv::Point(point.x + template_img_green.cols, point.y + template_img_green.rows),
        CV_RGB(0, 255, 0), 3);
  }

  // 探索画像の描画
  cv::imshow("input", src_img);           // 入力画像
  cv::imshow("result", result_img);       // 結果画像
  cv::imwrite("result.jpg", result_img);  // 結果画像の保存

  // キー入力待ち
  cv::waitKey(0);

  return 0;
}
