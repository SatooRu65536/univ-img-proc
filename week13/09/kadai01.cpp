#include <cmath>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <vector>

#define INPUT_IMAGE "./sample.jpg"

double calculate_circularity(const std::vector<cv::Point>& contour) {
  double area = cv::contourArea(contour);
  double perimeter = cv::arcLength(contour, true);
  if (perimeter == 0) {
    return 0;
  }
  return 4 * CV_PI * area / (perimeter * perimeter);
}

int main() {
  // 入力画像をカラーで読み込む
  cv::Mat image = cv::imread(INPUT_IMAGE, cv::IMREAD_COLOR);
  if (image.empty()) {
    fprintf(stderr, "画像を読み込めませんでした\n");
    return -1;
  }

  // グレースケールに変換し、エッジ検出
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  cv::Mat edges;
  cv::Canny(gray, edges, 100, 200);

  // 輪郭を求める
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  // 最大面積の円を見つける
  int max_area_contour_index = -1;
  double max_area = 0;

  for (size_t i = 0; i < contours.size(); i++) {
    double circularity = calculate_circularity(contours[i]);
    double area = cv::contourArea(contours[i]);
    if (circularity >= 0.8 && area > max_area) {
      max_area = area;
      max_area_contour_index = i;
    }
  }

  // 最大面積の円の輪郭を描画
  if (max_area_contour_index != -1) {
    cv::drawContours(image, contours, max_area_contour_index,
                     cv::Scalar(255, 255, 255), 2);
  } else {
    fprintf(stderr, "円形の輪郭が見つかりませんでした\n");
  }

  // 結果を表示
  cv::imshow("Result", image);
  cv::waitKey(0);

  return 0;
}
