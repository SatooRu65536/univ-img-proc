//
//  extractRegion4student.cpp
//  
//
//  Created by Masashi Morimoto on 2023/06/25.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#define FILE_NAME "fruit_image.jpg"

//ウィンドウ名
#define WINDOW_NAME_INPUT "input"
#define WINDOW_NAME_OUTPUT "output"

#define R_MIN () //Rのしきい値
#define G_MIN () //Gのしきい値
#define G_MAX () //Gのしきい値
#define B_MIN () //Bのしきい値
#define B_MAX () //Bのしきい値
#define WHITE_PIXEL (255) // 出力画像の値（白）

int main(int argc, const char * argv[]) {
    //変数の宣言
    int x, y; //走査用
    cv::Vec3b p; //色値
    
    //画像の宣言 (入力画像，出力画像)
    cv::Mat src_img, dst_img;
    
    // 1. カラー画像の入力
    src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
    if (src_img.empty()) { //入力失敗の場合
        fprintf(stderr, "Cannot read image file: %s.\n", FILE_NAME);
        return (-1);
    }

    // 2. 出力二値画像の領域を確保（初期値ゼロ：黒）
    dst_img = cv::Mat::zeros(src_img.size(), CV_8UC1);

    // 3. しきい値処理
    for (y=0; y<src_img.rows; y++) {
        for (x=0; x<src_img.cols; x++) {

            
            
            
            
        }
    }
    
    // 4. 表示
    cv::imshow(WINDOW_NAME_INPUT , src_img);//入力画像の表示
    cv::imshow(WINDOW_NAME_OUTPUT, dst_img);//出力画像の表示
    cv::waitKey(); //キー入力待ち (止める)
    
    return 0;
}
