#include <iostream>
#include <opencv2/opencv.hpp>

#define FILE_NAME "./three_objects.jpg"
#define HIGHVAL (255)
#define HIST_SIZE (256)

enum {
  BLUE,
  GREEN,
  RED,
};

int main(int argc, const char* argv[]) {
  double circle_per = 0.16;

  cv::Mat src_img = cv::imread(FILE_NAME, cv::IMREAD_COLOR);
  if (src_img.empty()) {
    fprintf(stderr, "File is not opened.\n");
    return -1;
  }

  // ヒストグラムの生成
  int hist[3][HIST_SIZE] = {0};
  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      cv::Vec3b vec = src_img.at<cv::Vec3b>(y, x);
      hist[BLUE][vec[BLUE]]++;
      hist[GREEN][vec[GREEN]]++;
      hist[RED][vec[RED]]++;
    }
  }

  //   //   csvファイルにヒストグラムを出力
  //   FILE* fp = fopen("hist.csv", "w");
  //   for (int i = 0; i < HIST_SIZE; i++) {
  //     fprintf(fp, "%d,%d,%d,%d\n", i, hist[BLUE][i], hist[GREEN][i],
  //             hist[RED][i]);
  //   }

  int th[3] = {0};
  int sum[3] = {0};

  for (int i = 0; i < 3; i++) {
    sum[i] = 0;
    for (int j = 0; j < HIST_SIZE; j++) {
      sum[i] += hist[i][j];
      if (sum[i] >= src_img.rows * src_img.cols * (1 - circle_per)) {
        th[i] = j;
        break;
      }
    }
  }

  printf("閾値: %d, %d, %d\n", th[BLUE], th[GREEN], th[RED]);

  cv::Mat result_img[3];
  for (int i = 0; i < 3; i++) {
    result_img[i] = cv::Mat(src_img.size(), CV_8UC3);
  }

  for (int y = 0; y < src_img.rows; y++) {
    for (int x = 0; x < src_img.cols; x++) {
      cv::Vec3b vec = src_img.at<cv::Vec3b>(y, x);
      if (vec[BLUE] >= th[BLUE]) {
        result_img[BLUE].at<cv::Vec3b>(y, x) = cv::Vec3b(HIGHVAL, 0, 0);
      }
      if (vec[GREEN] >= th[GREEN]) {
        result_img[GREEN].at<cv::Vec3b>(y, x) = cv::Vec3b(0, HIGHVAL, 0);
      }
      if (vec[RED] >= th[RED] && vec[GREEN] < th[GREEN]) {
        result_img[RED].at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, HIGHVAL);
      }
    }
  }

  cv::imshow("red", result_img[RED]);
  cv::imshow("green", result_img[GREEN]);
  cv::imshow("blue", result_img[BLUE]);
  cv::imwrite("output_red.jpg", result_img[RED]);
  cv::imwrite("output_green.jpg", result_img[GREEN]);
  cv::imwrite("output_blue.jpg", result_img[BLUE]);
  cv::waitKey();

  return 0;
}
