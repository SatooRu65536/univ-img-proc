#include <iostream>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE "sakura.jpg"
#define COLOR_NUM 256
#define IMAX 255

int main() {
  // カラー画像として画像を読み込む
  cv::Mat color_image = cv::imread(INPUT_IMAGE, cv::IMREAD_COLOR);

  // 画像が正常に読み込まれたか確認
  if (color_image.empty()) {
    std::cerr << "Could not open or find the image!" << std::endl;
    return -1;
  }

  // ルックアップテーブルの作成
  uchar lut[COLOR_NUM];
  for (int i = 0; i < COLOR_NUM; ++i) {
    lut[i] = IMAX - i;
  }

  // カラー画像をグレースケールに変換
  cv::Mat grayscale_image(color_image.size(), CV_8UC1);
  for (int y = 0; y < color_image.rows; ++y) {
    for (int x = 0; x < color_image.cols; ++x) {
      cv::Vec3b color = color_image.at<cv::Vec3b>(y, x);
      uchar gray = lut[static_cast<int>(0.299 * color[2] + 0.587 * color[1] +
                                        0.114 * color[0])];
      grayscale_image.at<uchar>(y, x) = gray;
    }
  }

  // グレースケール画像を表示
  cv::imshow("Grayscale Image", grayscale_image);

  // キーが押されるのを待つ
  cv::waitKey(0);

  return 0;
}
