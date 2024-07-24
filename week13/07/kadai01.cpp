#include <cstdio>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE_1 "issue_input1.jpg"
#define INPUT_IMAGE_2 "issue_input2.jpg"

// ガウシアンフィルタのサイズを推定する関数
int estimate_gaussian_filter_size(const cv::Mat& input_image1,
                                  const cv::Mat& input_image2) {
  int filter_size = 1;
  cv::Mat diff, blurred_image;
  int min_white_pixels = INT_MAX;

  for (int ksize = 1; ksize <= 31; ksize += 2) {
    cv::GaussianBlur(input_image2, blurred_image, cv::Size(ksize, ksize), 0);
    cv::absdiff(input_image1, blurred_image, diff);
    cv::threshold(diff, diff, 25, 255, cv::THRESH_BINARY);

    int white_pixels = cv::countNonZero(diff);
    if (white_pixels < min_white_pixels) {
      min_white_pixels = white_pixels;
      filter_size = ksize;
    }
  }

  return filter_size;
}

// 差分から加工部分を抽出する関数
cv::Mat extract_modified_area(const cv::Mat& input_image1,
                              const cv::Mat& input_image2, int filter_size) {
  cv::Mat blurred_image, diff, modified_area;

  cv::GaussianBlur(input_image2, blurred_image,
                   cv::Size(filter_size, filter_size), 0);
  cv::absdiff(input_image1, blurred_image, diff);

  cv::threshold(diff, modified_area, 25, 255, cv::THRESH_BINARY);

  return modified_area;
}

// 差分を赤色で表示する関数
cv::Mat display_difference_in_red(const cv::Mat& modified_area) {
  cv::Mat result_image = cv::Mat::zeros(modified_area.size(), CV_8UC3);

  for (int y = 0; y < modified_area.rows; ++y) {
    for (int x = 0; x < modified_area.cols; ++x) {
      if (modified_area.at<uchar>(y, x) == 255) {
        result_image.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 255);  // 赤色
      }
    }
  }

  return result_image;
}

int main() {
  // 入力画像を読み込む
  cv::Mat input_image1 = cv::imread(INPUT_IMAGE_1, cv::IMREAD_GRAYSCALE);
  cv::Mat input_image2 = cv::imread(INPUT_IMAGE_2, cv::IMREAD_GRAYSCALE);

  if (input_image1.empty() || input_image2.empty()) {
    fprintf(stderr, "Error: Could not open or find the images.\n");
    return -1;
  }

  // ガウシアンフィルタのサイズを推定
  int filter_size = estimate_gaussian_filter_size(input_image1, input_image2);
  fprintf(stdout, "Estimated Gaussian filter size: %d\n", filter_size);

  // 加工部分を差分から抽出
  cv::Mat modified_area =
      extract_modified_area(input_image1, input_image2, filter_size);

  // 差分を赤色で表示
  cv::Mat result_image = display_difference_in_red(modified_area);

  // 結果を表示
  cv::imshow("Input Image 1", input_image1);
  cv::imshow("Input Image 2", input_image2);
  cv::imshow("Modified Area in Red", result_image);

  cv::waitKey(0);
  return 0;
}
