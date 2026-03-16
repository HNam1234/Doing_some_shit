#include <iostream>
#include <cstdint>
#include <vector>
#include <opencv2/opencv.hpp>

int IMAGE_WIDTH = 169;
int IMAGE_HEIGHT = 23;

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int main() {
    RGB redColor = {255, 0, 0};
    std::vector<RGB> colors;
    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; ++i) {
        if (i >= IMAGE_HEIGHT * IMAGE_WIDTH / 2) {
            RGB greenColor = {0, 255, 0};
            colors.push_back(greenColor);
            continue;
        }
        colors.push_back(redColor);
    }

    cv::Mat frame(IMAGE_HEIGHT, IMAGE_WIDTH, CV_8UC3, colors.data());

    cv::Mat bgr;
    cv::cvtColor(frame, bgr, cv::COLOR_RGB2BGR);

    // Save or process
    cv::imwrite("output.png", bgr);
    return 0;
}
