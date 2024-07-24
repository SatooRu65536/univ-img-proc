#include <opencv2/opencv.hpp>
#include <iostream>

#define INPUT_IMAGE_PATH "./image1.jpg"

int main() {
    // Load the image in grayscale
    cv::Mat gray_image = cv::imread(INPUT_IMAGE_PATH, cv::IMREAD_GRAYSCALE);

    if (gray_image.empty()) {
        std::cerr << "Error: Could not load image." << std::endl;
        return -1;
    }

    // Apply thresholding to binarize the image
    cv::Mat binary_image;
    int threshold_value = 128; // Example threshold value
    cv::threshold(gray_image, binary_image, threshold_value, 255, cv::THRESH_BINARY);

    // Invert the image so the object becomes white and background becomes black
    cv::Mat inverted_image;
    cv::bitwise_not(binary_image, inverted_image);

    // Display the original and processed images
    cv::imshow("Original Image", gray_image);
    cv::imshow("Binary Image", binary_image);
    cv::imshow("Inverted Image", inverted_image);

    // Wait for a key press indefinitely
    cv::waitKey(0);

    return 0;
}
