#include <iostream>
#include <opencv2/opencv.hpp>

// ファイル
#define FILE_NAME "sample_rotate.jpg"

// 二値化しきい値
#define BIN_TH (100)

struct Feature {
  int index;
  double area;
  double circularity;
  cv::Rect rect;
};

int main(int argc, const char* argv[]) {
  // 画像の宣言
  // (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
  cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

  // 輪郭の座標リストの宣言 (New!)
  std::vector<std::vector<cv::Point>> contours;

  // 画像の入力 (カラーで入力)
  src_img = cv::imread(FILE_NAME);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "File is not opened.\n");
    return (-1);
  }

  // 入力画像を出力画像にコピー (New!)
  dst_img = src_img.clone();

  // グレースケール化
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 二値化
  cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

  // 二値画像コピー
  tmp_img = bin_img.clone();

  cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  std::vector<Feature> rects;
  // 面積と円形度を計算
  for (int i = 0; i < contours.size(); i++) {
    Feature feature;
    feature.index = i;
    feature.area = cv::contourArea(contours[i]);
    feature.circularity =
        4 * M_PI * feature.area / pow(cv::arcLength(contours[i], true), 2);
    feature.rect = cv::boundingRect(contours[i]);

    int size = feature.rect.width * feature.rect.height;
    int diff = abs(size - feature.area);

    // 面積と矩形の面積の差が 10% 未満の場合 は 四角！！
    if (diff / (double)size < 0.1) {
      printf("index: %d, size: %d\n", feature.index, size);
      rects.push_back(feature);
    }
  }

  // 最も面積が小さい四角を描画
  Feature min_rect = rects[0];
  for (int i = 1; i < rects.size(); i++) {
    if (min_rect.area > rects[i].area) {
      min_rect = rects[i];
    }
  }

  // 塗りつぶし
  cv::drawContours(dst_img, contours, min_rect.index, CV_RGB(255, 0, 255), -1);

  // 表示
  cv::imshow("src image", src_img);
  cv::imshow("binary image", bin_img);
  cv::imshow("outpu image", dst_img);
  cv::imwrite("output.jpg", dst_img);
  cv::waitKey();

  return 0;
}
