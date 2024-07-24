#include <opencv2/opencv.hpp>
#include <iostream>

#define INPUT_IMAGE "./ham.jpg"

int main() {
    // 画像を読み込む
    cv::Mat input_image = cv::imread(INPUT_IMAGE, cv::IMREAD_GRAYSCALE);
    if (input_image.empty()) {
        std::cerr << "画像が読み込めませんでした。" << std::endl;
        return -1;
    }

    // 縦方向の微分フィルタ
    double filter_v[3][3] = {
        {0, 0, 0},
        {-1, 0, 1},
        {0, 0, 0}
    };
    cv::Mat kernel_v = cv::Mat(3, 3, CV_64F, filter_v);

    // 横方向の微分フィルタ
    double filter_h[3][3] = {
        {0, -1, 0},
        {0, 0, 0},
        {0, 1, 0}
    };
    cv::Mat kernel_h = cv::Mat(3, 3, CV_64F, filter_h);

    // フィルタリング結果を格納する行列
    cv::Mat grad_x, grad_y;

    // フィルタリングを行う
    cv::filter2D(input_image, grad_x, CV_64F, kernel_v);
    cv::filter2D(input_image, grad_y, CV_64F, kernel_h);

    // 勾配の大きさを計算する
    cv::Mat grad_magnitude;
    cv::magnitude(grad_x, grad_y, grad_magnitude);

    // 勾配の大きさを正規化して表示用に変換
    cv::Mat grad_magnitude_display;
    cv::normalize(grad_magnitude, grad_magnitude_display, 0, 255, cv::NORM_MINMAX, CV_8U);

    // 結果を表示
    cv::imshow("Input Image", input_image);
    cv::imshow("Gradient Magnitude", grad_magnitude_display);
    cv::waitKey(0);

    return 0;
}
