#include <opencv2/opencv.hpp>
#include <cstdio>

#define INPUT_IMAGE "./issue1.jpg"

// 色値の設定
cv::Scalar color[] = {
    CV_RGB(255, 0, 0),
    CV_RGB(0, 255, 0),
    CV_RGB(0, 0, 255),
    CV_RGB(255, 0, 255)
};

// 円形度を計算する関数
double circularity(const std::vector<cv::Point>& contour) {
    double perimeter = cv::arcLength(contour, true);
    double area = cv::contourArea(contour);
    return (4 * CV_PI * area) / (perimeter * perimeter);
}

int main() {
    // 画像の読み込み
    cv::Mat src = cv::imread(INPUT_IMAGE, cv::IMREAD_GRAYSCALE);
    if (src.empty()) {
        fprintf(stderr, "Failed to load image %s\n", INPUT_IMAGE);
        return -1;
    }

    // 画像の二値化
    cv::Mat binary;
    cv::threshold(src, binary, 127, 255, cv::THRESH_BINARY);

    // 膨張処理
    cv::Mat dilated;
    cv::dilate(binary, dilated, cv::Mat(), cv::Point(-1, -1), 20);

    // 収縮処理
    cv::Mat eroded;
    cv::erode(dilated, eroded, cv::Mat(), cv::Point(-1, -1), 20);

    // 輪郭の検出
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(eroded, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // マスク画像の作成
    cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC3);

    int color_idx = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        double circ = circularity(contours[i]);
        if (circ < 0.8) {
            cv::drawContours(mask, contours, (int)i, color[color_idx % 4], -1, cv::LINE_8, hierarchy, 1);
            color_idx++;
        }
    }

    // 結果の表示
    cv::imshow("Mask", mask);
    cv::waitKey(0);

    return 0;
}
