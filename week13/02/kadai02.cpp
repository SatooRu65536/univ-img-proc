#include <iostream>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE "aquarium.jpg"

int main() {
  // 画像を読み込む
  cv::Mat image = cv::imread(INPUT_IMAGE);

  // 画像が正常に読み込まれたか確認
  if (image.empty()) {
    std::cerr << "Error: Unable to open input image!" << std::endl;
    return -1;
  }

  // 画像の高さの半分を計算
  int halfHeight = image.rows / 2;

  // 下半分を赤成分のみに変換
  for (int y = halfHeight; y < image.rows; ++y) {
    for (int x = 0; x < image.cols; ++x) {
      cv::Vec3b& pixel = image.at<cv::Vec3b>(y, x);
      // 青と緑の成分を0にする
      pixel[0] = 0;  // 青
      pixel[1] = 0;  // 緑
                     // 赤成分はそのまま
    }
  }

  // 変換後の画像を表示
  cv::imshow("Transformed Image", image);
  cv::waitKey(0);

  return 0;
}
