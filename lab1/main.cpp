#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

int
main()
{
    constexpr size_t cx_rows{500};
    constexpr size_t cx_cols{500};

    cv::Mat image(cx_rows, cx_cols, CV_8UC3);

    for(size_t row{0}; row < cx_rows; ++row)
        for(size_t col{0}; col < cx_cols; ++col)
            for (size_t ch{0}; ch < image.channels(); ++ch)
                image.at<cv::Vec3b>(row, col) = cv::Vec3b(255 * abs(sin(10000 * row) * cos(10000 * col)), 
                                                          255 * abs(cos(10000 * col) * sin(10000 * row)),  
                                                          255 * abs(sin(10000 * col) * sin (10000 * row))); 

    cv::cvtColor(image, image, CV_BGR2RGB);
    cv::imshow("Image", image);
    cv::imwrite("image.jpeg", image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));
    cv::waitKey();

   	return 0;
}
