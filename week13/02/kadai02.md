**You:**

制約に従って以下のプログラムを書いてください

aquarium.jpg という画像を読み込み、下半分を赤成分のみに変換する.
変換後の画像を表示する


# 制約
言語はC++
OpenCVを使う
入力画像はマクロで定義しておく
必ず cv:: というnamespaceをつける

* * *

**ChatGPT:**

以下のC++プログラムでは、OpenCVを使用して画像を読み込み、下半分を赤成分のみに変換し、変換後の画像を表示します。指定された制約に従っています。

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

#define INPUT_IMAGE "aquarium.jpg"

int main() {
    // 画像を読み込む
    cv::Mat image = cv::imread(INPUT_IMAGE);

    // 画像が正常に読み込まれたか確認
    if(image.empty()) {
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
            pixel[0] = 0; // 青
            pixel[1] = 0; // 緑
            // 赤成分はそのまま
        }
    }

    // 変換後の画像を表示
    cv::imshow("Transformed Image", image);
    cv::waitKey(0);

    return 0;
}
```

このプログラムは、以下の手順を実行します。

1. `INPUT_IMAGE`マクロで定義された画像を読み込む。
2. 画像が正常に読み込まれたかを確認する。
3. 画像の高さの半分を計算する。
4. 下半分の各ピクセルについて、赤成分以外（青と緑）を0にする。
5. 変換後の画像を表示する。

このプログラムを実行するには、OpenCVライブラリがインストールされている必要があります。また、コンパイル時に適切なOpenCVのリンクオプションを指定してください。例えば、以下のようにコンパイルします。

```sh
g++ -o transform_image transform_image.cpp `pkg-config --cflags --libs opencv4`
```

このコマンドを実行すると、プログラムがコンパイルされ、`transform_image`という実行ファイルが生成されます。次に、この実行ファイルを実行して画像を変換・表示できます。

```sh
./transform_image
```
