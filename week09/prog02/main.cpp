#include <iostream>
#include <opencv2/opencv.hpp>

// ファイル
#define FILE_NAME "sample.jpg"

// 二値化しきい値
#define BIN_TH (100)

int main(int argc, const char* argv[]) {
  // 画像の宣言
  // (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
  cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

  // 輪郭の座標リストの宣言 (New!)
  std::vector<std::vector<cv::Point> > contours;

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

  // 輪郭数の表示
  fprintf(stdout, "輪郭数: %lu\n", contours.size());

  // 表示する輪郭番号の入力
  int contour_num;
  fprintf(stdout, "輪郭番号(0~%lu): ", contours.size() - 1);
  scanf("%d", &contour_num);

  // 領域特徴量の取得・表示
  double area = cv::contourArea(contours[contour_num]);
  fprintf(stdout, "面積: %f\n", area);

  // 輪郭の周囲長
  double perimeter = cv::arcLength(contours[contour_num], true);
  fprintf(stdout, "周囲長: %f\n", perimeter);

  // 外接長方形の取得
  cv::Rect rect = cv::boundingRect(contours[contour_num]);

  // 外接長方形の描画
  cv::rectangle(dst_img, rect, cv::Scalar(255, 0, 255), 2);

  // 表示
  cv::imshow("src image", src_img);
  cv::imshow("binary image", bin_img);
  cv::imshow("outpu image", dst_img);
  cv::waitKey();

  return 0;
}
