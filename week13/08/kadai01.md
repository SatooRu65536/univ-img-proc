**You:**

制約に従って以下のプログラムを書いてください

入力画像("./ptile.jpg")をグレースケールとして読み込んでください
画像のうち、1/4が別の色の文字です.この情報を元に ouble p = 4.0 / (4.0 + 1.0); を使ってヒストグラム用の配列を使用して，度数0(背景)から走査して，該当の面積に到達する度数(閾値)を求めた上で二値化して表示してください

# 制約
言語はC++
OpenCVを使う
入力画像はマクロで定義しておく
必ず cv:: というnamespaceをつける
変数名等はスネークケースで書く
std::cout,std::cerr ではなく、fprintf 等を使う

* * *

**ChatGPT:**

以下は指定された条件に従って作成されたC++プログラムです。このプログラムはOpenCVを使用して、入力画像をグレースケールで読み込み、ヒストグラムを計算して閾値を決定し、二値化された画像を表示します。

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

#define INPUT_IMAGE "./ptile.jpg"

int main() {
    // 入力画像をグレースケールで読み込む
    cv::Mat gray_image = cv::imread(INPUT_IMAGE, cv::IMREAD_GRAYSCALE);
    if (gray_image.empty()) {
        fprintf(stderr, "Could not open or find the image\n");
        return -1;
    }

    // ヒストグラムの計算
    int hist_size = 256;
    float range[] = {0, 256};
    const float* hist_range = {range};
    cv::Mat hist;
    cv::calcHist(&gray_image, 1, 0, cv::Mat(), hist, 1, &hist_size, &hist_range);

    // ヒストグラムの累積度数を計算
    std::vector<float> cumulative_hist(hist_size, 0);
    cumulative_hist[0] = hist.at<float>(0);
    for (int i = 1; i < hist_size; i++) {
        cumulative_hist[i] = cumulative_hist[i - 1] + hist.at<float>(i);
    }

    // 全ピクセル数と閾値の計算
    double total_pixels = gray_image.rows * gray_image.cols;
    double threshold_area = total_pixels * (4.0 / (4.0 + 1.0));

    // 閾値を見つける
    int threshold = 0;
    for (int i = 0; i < hist_size; i++) {
        if (cumulative_hist[i] >= threshold_area) {
            threshold = i;
            break;
        }
    }

    // 二値化
    cv::Mat binary_image;
    cv::threshold(gray_image, binary_image, threshold, 255, cv::THRESH_BINARY);

    // 二値化された画像を表示
    cv::imshow("Binary Image", binary_image);
    cv::waitKey(0);

    return 0;
}
```

このプログラムのポイントは次の通りです：

1. 入力画像をグレースケールで読み込みます。
2. ヒストグラムを計算し、累積度数を求めます。
3. `ouble p = 4.0 / (4.0 + 1.0);` から計算した割合を用いて閾値を決定します。
4. 閾値を用いて画像を二値化し、結果を表示します。

`cv::imread`関数で画像を読み込み、`cv::calcHist`関数でヒストグラムを計算し、`cv::threshold`関数で二値化を行っています。最終的な二値化された画像は`cv::imshow`で表示されます。
