#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

int
main(int argc, const char* argv[])
{
    std::string save_path;

    if (argc == 1)
        save_path = "../resources/image.jpeg";
    else if (argc == 2)
    {
        save_path += argv[1];
        save_path += "/image.jpeg";
    }

    constexpr size_t cx_rows{500};
    constexpr size_t cx_cols{500};

    cv::Mat image(cx_rows, cx_cols, CV_8UC3);
    cv::cvtColor(image, image,  CV_BGR2HSV);

    for(size_t row{0}; row < cx_rows; ++row)
        for(size_t col{0}; col < cx_cols; ++col)
            for (size_t ch{0}; ch < image.channels(); ++ch)
                image.at<cv::Vec3b>(row, col) = cv::Vec3b(255 * abs(sin(col * row * 10000)), 
                                                          255 * abs(cos(row * col * 10000)),  
                                                          255 * abs(sin(row * col * 10000))); 

    cv::cvtColor(image, image, CV_HSV2RGB);
    cv::imshow("Image", image);
    cv::imwrite(save_path, image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));

    cv::waitKey();

   	return 0;
}
