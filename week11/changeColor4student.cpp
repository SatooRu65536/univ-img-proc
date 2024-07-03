//
//  changeColor4student.cpp
//  
//
//  Created by Masashi Morimoto on 2024/06/25.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"
// 0. 定数の定義
#define HUE_DIFF (90) //Hの変化量
#define SAT_DIFF (50) //Sの変化量
#define VAL_DIFF (50) //Vの変化量
#define HUE_MIN (0) // Hの最小値
#define HUE_MAX (180) // Hの最大値（シフト幅）
#define SAT_MIN (0) // Sの最小値
#define VAL_MIN (0) // Vの最小値


int main(int argc, const char * argv[]) {
    // 1. 変数の宣言
    int x, y;    //走査用
    cv::Vec3b p; //色値(HSV)
    int h,s,v;   //色値(各要素)
    cv::Mat src_img, hsv_img, dst_img; //入力画像，HSV画像，出力画像

    // 2. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }
    
    // 3. 色変換 (BGR → HSV)
    

    // 4. 画像処理

    
    // 5. 色変換 (HSV → BGR)

    
    // 6. 表示
    cv::imshow(WINDOW_NAME_INPUT , src_img); // 入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img); // 出力画像の表示
    cv::waitKey(); // キー入力待ち (止める)
    return 0;
}

