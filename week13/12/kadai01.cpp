#include <opencv2/opencv.hpp>
#include <iostream>

#define INPUT_IMAGE "gazoDora.jpg"
#define TEMPLATE_GREEN "green.jpg"
#define TEMPLATE_RED "red.jpg"
#define TEMPLATE_STAR "star.jpg"
#define TEMPLATE_YELLOW "yellow.jpg"
#define MATCH_THRESHOLD 0.05  // 閾値（適宜調整）

void detect_and_draw(cv::Mat& input_image, const cv::Mat& template_image, const cv::Scalar& color, const char* template_name) {
    cv::Mat result;
    int result_cols = input_image.cols - template_image.cols + 1;
    int result_rows = input_image.rows - template_image.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1);

    cv::matchTemplate(input_image, template_image, result, cv::TM_SQDIFF_NORMED);

    for (int y = 0; y < result.rows; y++) {
        for (int x = 0; x < result.cols; x++) {
            if (result.at<float>(y, x) <= MATCH_THRESHOLD) {
                cv::Point match_loc(x, y);
                cv::rectangle(input_image, match_loc, cv::Point(match_loc.x + template_image.cols, match_loc.y + template_image.rows), color, 6, 8, 0);
                fprintf(stderr, "Detected template %s at location (%d, %d) with value %f\n", template_name, match_loc.x, match_loc.y, result.at<float>(y, x));
            }
        }
    }
}

int main() {
    cv::Mat input_image = cv::imread(INPUT_IMAGE, cv::IMREAD_COLOR);
    if (input_image.empty()) {
        fprintf(stderr, "Could not open or find the input image\n");
        return -1;
    }

    cv::Mat template_green = cv::imread(TEMPLATE_GREEN, cv::IMREAD_COLOR);
    cv::Mat template_red = cv::imread(TEMPLATE_RED, cv::IMREAD_COLOR);
    cv::Mat template_star = cv::imread(TEMPLATE_STAR, cv::IMREAD_COLOR);
    cv::Mat template_yellow = cv::imread(TEMPLATE_YELLOW, cv::IMREAD_COLOR);

    if (template_green.empty() || template_red.empty() || template_star.empty() || template_yellow.empty()) {
        fprintf(stderr, "Could not open or find one of the template images\n");
        return -1;
    }

    detect_and_draw(input_image, template_green, CV_RGB(0, 255, 0), "green");
    detect_and_draw(input_image, template_red, CV_RGB(255, 0, 0), "red");
    detect_and_draw(input_image, template_star, CV_RGB(255, 0, 255), "star");
    detect_and_draw(input_image, template_yellow, CV_RGB(255, 255, 0), "yellow");

    cv::imshow("Detected Templates", input_image);
    cv::waitKey(0);
    return 0;
}
