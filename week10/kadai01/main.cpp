#include <stdio.h>

#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "issue1.jpg"

// 二値化閾値
#define BIN_TH (100)

struct ChildFeature {
  int index;
  int size;
};

struct Feature {
  int index;
  cv::Rect rect;
  ChildFeature child;
};

int main(int argc, const char* argv[]) {
  // 1. 画像の宣言
  // (入力画像，グレースケール画像，二値画像，一時的な画像，出力画像)
  cv::Mat src_img, gray_img, bin_img, tmp_img, dst_img;

  // 色値の設定
  cv::Scalar color[] = {
      CV_RGB(255, 0, 0),   //
      CV_RGB(0, 255, 0),   //
      CV_RGB(0, 0, 255),   //
      CV_RGB(255, 0, 255)  //
  };

  // 2. 輪郭の座標リストの宣言
  std::vector<std::vector<cv::Point> > contours;

  // 3. 画像の入力 (カラーで入力)
  src_img = cv::imread(FILE_NAME);
  if (src_img.empty()) {  // 入力失敗の場合
    fprintf(stderr, "File is not opened.\n");
    return (-1);
  }

  // 4. 入力画像を結果画像にコピー
  dst_img = src_img.clone();

  // 5. グレースケール化
  cv::cvtColor(src_img, gray_img, cv::COLOR_BGR2GRAY);

  // 6. 二値化 (固定閾値で実装．閾値: 100)
  cv::threshold(gray_img, bin_img, BIN_TH, 255, cv::THRESH_BINARY);

  // 二値画像コピー
  tmp_img = bin_img.clone();

  // 7. 輪郭抽出
  cv::findContours(tmp_img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

  // 8. 円以外を抽出
  std::vector<Feature> feature;
  for (int i = 0; i < contours.size(); i++) {
    // 面積と円形度
    double area = cv::contourArea(contours[i]);
    double circularity =
        4 * M_PI * area / pow(cv::arcLength(contours[i], true), 2);

    // 円は除外
    if (circularity > 0.8) continue;

    Feature f;
    f.index = i;
    f.rect = cv::boundingRect(contours[i]);
    f.child.index = -1;
    f.child.size = 0;

    feature.push_back(f);
  }

  // 子供を探す旅
  for (int i = 0; i < feature.size(); i++) {
    for (int j = 0; j < feature.size(); j++) {
      if (i == j) continue;

      Feature target = feature[j];

      // feature[i].tl(親) が target.tl より右下にあれば 子 ではない
      if (feature[i].rect.tl().x < target.rect.tl().x) continue;
      if (feature[i].rect.tl().y < target.rect.tl().y) continue;

      // feature[i].br(親) が target.br より左上にあれば 子 ではない
      if (feature[i].rect.br().x > target.rect.br().x) continue;
      if (feature[i].rect.br().y > target.rect.br().y) continue;

      // 子供だ！！！
      ChildFeature findedChild;
      findedChild.index = target.index;
      findedChild.size = target.rect.width * target.rect.height;

      // 一番大きい子供を選ぶ(孫はいらない)
      printf("親?:%d:%d, 子?:%d:%d\n", feature[i].index, feature[i].child.size,
             findedChild.index, findedChild.size);
      if (feature[i].child.size < findedChild.size) {
        feature[i].child.index = findedChild.index;
        feature[i].child.size = findedChild.size;
      }
    }
  }

  // 出力
  for (int i = 0; i < feature.size(); i++) {
    printf("親:%d, 子:%d\n", feature[i].index, feature[i].child.index);
  }

  // 9. 表示
  cv::imshow("output", dst_img);
  cv::waitKey();

  return 0;
}
