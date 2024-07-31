#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "gem2.jpg"

#define MAX_VAL (255)

#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_BINARY "binary"
#define WINDOW_NAME_OUTPUT "output"

enum {
  RED,
  GREEN,
  BLUE,
};

enum {
  HUE,
  SAT,
  VAL,
};

bool is_black(double gray) { return gray < 25; }

bool is_green(cv::Vec3b rgb) {
  if (rgb[RED] <= 0 || rgb[RED] >= 150) return 0;
  if (rgb[GREEN] <= 50 || rgb[GREEN] >= 100) return 0;
  if (rgb[BLUE] <= 0 || rgb[BLUE] >= 50) return 0;

  return 1;
}

bool is_golden(cv::Vec3b hsv) {
  if (hsv[HUE] <= 20 || hsv[HUE] >= 60) return 0;
  if (hsv[SAT] <= 100 || hsv[SAT] >= 200) return 0;

  return 1;
}

std::vector<std::vector<cv::Point>> find_contours(cv::Mat img) {
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  return contours;
}

cv::Mat drawed_circle(cv::Mat img,
                      std::vector<std::vector<cv::Point>> contours) {
  cv::Mat tmp = img.clone();
  for (int i = 0; i < contours.size(); i++) {
    float radius;
    cv::Point2f center;
    cv::minEnclosingCircle(contours[i], center, radius);
    cv::circle(tmp, center, (int)radius, CV_RGB(255, 0, 0), 2);
  }

  return tmp;
}

cv::Mat drawed_rectangle(cv::Mat img,
                         std::vector<std::vector<cv::Point>> contours) {
  cv::Mat tmp = img.clone();
  for (int i = 0; i < contours.size(); i++) {
    cv::Rect rect = cv::boundingRect(contours[i]);
    cv::rectangle(tmp, rect, CV_RGB(255, 255, 255), 2);
  }

  return tmp;
}

// 塗りつぶす
cv::Mat filled(cv::Mat img, std::vector<std::vector<cv::Point>> contours) {
  cv::Mat tmp = img.clone();
  for (int i = 0; i < contours.size(); i++) {
    cv::drawContours(tmp, contours, i, CV_RGB(0, 255, 0), -1);
  }

  return tmp;
}

int main(int argc, const char* argv[]) {
  // 画像を入力
  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
  if (src_img.empty()) {
    fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
    return (-1);
  }

  // グレースケール画像
  cv::Mat gray_img;
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // HSV画像
  cv::Mat hsv_img;
  cv::cvtColor(src_img, hsv_img, cv::COLOR_BGR2HSV);

  cv::Mat black_gem_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
  cv::Mat green_gem_img = cv::Mat::zeros(src_img.size(), CV_8UC1);
  cv::Mat golden_gem_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

  // しきい値処理
  for (int y = 0; y < hsv_img.rows; y++) {
    for (int x = 0; x < hsv_img.cols; x++) {
      cv::Vec3b rgb = src_img.at<cv::Vec3b>(y, x);
      cv::Vec3b hsv = hsv_img.at<cv::Vec3b>(y, x);
      double gray = gray_img.at<uchar>(y, x);

      if (is_black(gray))
        black_gem_img.at<uchar>(y, x) = MAX_VAL;
      else if (is_green(rgb))
        green_gem_img.at<uchar>(y, x) = MAX_VAL;
      else if (is_golden(hsv))
        golden_gem_img.at<uchar>(y, x) = MAX_VAL;
    }
  }

  // 黒 を膨張・収縮
  cv::dilate(black_gem_img, black_gem_img, cv::Mat(), cv::Point(-1, -1), 15);
  cv::erode(black_gem_img, black_gem_img, cv::Mat(), cv::Point(-1, -1), 15);

  // 緑 を膨張・収縮
  cv::erode(green_gem_img, green_gem_img, cv::Mat(), cv::Point(-1, -1), 1);
  cv::dilate(green_gem_img, green_gem_img, cv::Mat(), cv::Point(-1, -1), 10);
  cv::erode(green_gem_img, green_gem_img, cv::Mat(), cv::Point(-1, -1), 7);

  // ゴールド を膨張・収縮
  cv::dilate(golden_gem_img, golden_gem_img, cv::Mat(), cv::Point(-1, -1), 5);
  cv::erode(golden_gem_img, golden_gem_img, cv::Mat(), cv::Point(-1, -1), 5);

  // 輪郭追跡による領域検出
  std::vector<std::vector<cv::Point>> black_gem_contours =
      find_contours(black_gem_img);
  std::vector<std::vector<cv::Point>> green_gem_contours =
      find_contours(green_gem_img);
  std::vector<std::vector<cv::Point>> golden_gem_contours =
      find_contours(golden_gem_img);

  // 出力画像
  cv::Mat dst_img = src_img.clone();

  // 黒 は外接長方形で囲む
  dst_img = drawed_rectangle(dst_img, black_gem_contours);
  // 緑 は塗りつぶす
  dst_img = filled(dst_img, green_gem_contours);
  // ゴールド は外接円で囲む
  dst_img = drawed_circle(dst_img, golden_gem_contours);

  // 個数を出力
  fprintf(stderr, "Black gem = %zu\n", black_gem_contours.size());
  fprintf(stderr, "Green gem = %zu\n", green_gem_contours.size());
  fprintf(stderr, "Golden gem = %zu\n", golden_gem_contours.size());

  cv::imshow(WINDOW_NAME_OUTPUT, dst_img);
  cv::waitKey();  // キー入力待ち (止める)

  return 0;
}
