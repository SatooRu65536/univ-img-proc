//
//  colorBar4student.cpp
//  
//
//  Created by Masashi Morimoto on 2024/06/25.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#define IMG_WIDTH (180) //画像の幅
#define IMG_HEIGHT (100) //画像の高さ
#define HUE_MAX (180) //Hの最大
#define SAT_MAX (255) //Sの最大
#define VAL_MAX (255) //Vの最大

int main(int argc, const char * argv[]) {
    //1. 変数の宣言
    int h, y; //色相と画像の縦方向位置
    cv::Vec3b p; //色値(HSV)
    
    //2. HSV画像・BGR画像領域の確保 3チャンネル画像
    cv::Mat hsv_img, bgr_img;
    hsv_img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HEIGHT), CV_8UC3);
    bgr_img = cv::Mat(cv::Size(IMG_WIDTH, IMG_HEIGHT), CV_8UC3);
    
    //3. カラーバーの作成

    //4. 色変換 (HSV → BGR)

    //5. 表示
    cv::imshow("Hue Bar", bgr_img);
    cv::waitKey();
    return 0;
}
