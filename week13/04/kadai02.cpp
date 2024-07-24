#include <cstdio>
#include <opencv2/opencv.hpp>

#define INPUT_IMAGE_PATH "./image2.jpg"
#define OUTPUT_FILE_PATH "04_023_k23075.txt"

int main() {
  // Load the image in grayscale
  cv::Mat gray_image = cv::imread(INPUT_IMAGE_PATH, cv::IMREAD_GRAYSCALE);

  if (gray_image.empty()) {
    fprintf(stderr, "Error: Could not load image.\n");
    return -1;
  }

  // Apply thresholding to binarize the image
  cv::Mat binary_image;
  int threshold_value = 121;  // Threshold value as specified
  cv::threshold(gray_image, binary_image, threshold_value, 255,
                cv::THRESH_BINARY);

  // Invert the image so the object becomes white and background becomes black
  cv::Mat inverted_image;
  cv::bitwise_not(binary_image, inverted_image);

  // Count the number of white pixels (object area)
  int object_area = cv::countNonZero(inverted_image);

  // Display the original and processed images
  cv::imshow("Original Image", gray_image);
  cv::imshow("Binary Image", binary_image);
  cv::imshow("Inverted Image", inverted_image);

  // Print the object area to the console
  fprintf(stdout, "Object area (number of white pixels): %d\n", object_area);

  // Write the object area to the output file
  FILE *output_file = fopen(OUTPUT_FILE_PATH, "w");
  if (output_file == nullptr) {
    fprintf(stderr, "Error: Could not open output file.\n");
    return -1;
  }
  fprintf(output_file, "image2=%d\n", object_area);
  fclose(output_file);

  // Wait for a key press indefinitely
  cv::waitKey(0);

  return 0;
}
