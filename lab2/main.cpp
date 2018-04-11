#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

int
main()
{
    constexpr uint8_t cx_white{255};
    constexpr uint8_t cx_black{0};
    constexpr uint8_t cx_threshhold{255/2};
    constexpr uint8_t cx_v{2};

    cv::Mat image;
    image = cv::imread("shiro.png");
    cv::cvtColor(image, image, CV_BGR2HSV);

    cv::Mat image_bin(image.rows, image.cols, CV_8UC1);
    
    for(size_t row{0}; row < image.rows; ++row)
        for (size_t col{0}; col < image.cols; ++col)
            if (image.at<cv::Vec3b>(row, col)[cx_v] > cx_threshhold)
                image_bin.at<uint8_t>(row, col) = cx_white; 
            else 
                image_bin.at<uint8_t>(row, col) = cx_black;

    cv::imshow("Image bin", image_bin);
    cv::imwrite("image_bin.jpeg", image_bin, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));
    cv::waitKey();

   	return 0;

}
