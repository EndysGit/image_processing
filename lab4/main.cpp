#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

size_t 
get_index_inf(ptrdiff_t ind, size_t demnsion_size)
{
    return  (ind >= 0 && ind < demnsion_size) ? 
        ind : abs(ind + static_cast<ptrdiff_t>(demnsion_size));
}

int
main(int argc, char *argv[])
{
    cv::Mat image;
    if (argc == 2)
        image = cv::imread(argv[1]);
    if (argc == 1)
        image = cv::imread("../resources/shiro.png");
    
    const cv::Size sz(image.cols/2, image.rows/2);
    cv::resize(image, image, sz);
    
    cv::Mat processed_image;
    
    // the Filter
    // ----------
    cv::filter2D(image, processed_image, -1, std::vector<float>({-0.5, 0.5}));
    cv::imshow("core filter", processed_image);
    cv::imwrite("../resources/core.jpeg", image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));
    
    // Ones Filter 
    // -----------
    size_t ones_kernel_sz{5};
    cv::Mat ones_kernel = cv::Mat::ones(ones_kernel_sz, ones_kernel_sz, CV_32F)/static_cast<float>(ones_kernel_sz * ones_kernel_sz);
    cv::filter2D(image, processed_image, -1, ones_kernel);
    cv::imshow("ones", processed_image);
    cv::imwrite("../resources/ones.jpeg", image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));
    
    // Blur filter
    // -----------
    cv::Mat blur_kernel(3,3, CV_32F);

    blur_kernel.at<float>(0, 0) = 1;
    blur_kernel.at<float>(0, 1) = 2;
    blur_kernel.at<float>(0, 2) = 1;

    blur_kernel.at<float>(1, 0) = 2;
    blur_kernel.at<float>(1, 1) = 4;
    blur_kernel.at<float>(1, 2) = 2;

    blur_kernel.at<float>(2, 0) = 1;
    blur_kernel.at<float>(2, 1) = 2;
    blur_kernel.at<float>(2, 2) = 1;
    blur_kernel /= static_cast<float>(16);
    cv::filter2D(image, processed_image, -1, blur_kernel);
    cv::imshow("blur", processed_image);
    cv::imwrite("../resources/blur.jpeg", image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));

    // Median filter
    // ------------
    image.copyTo(processed_image); 
    ptrdiff_t  median_kernel_sz{10};
    std::vector<uint8_t> window_elements_h, window_elements_s, window_elements_v; 
    for (ptrdiff_t row{0}; row < processed_image.rows; ++row)
    {
        for (ptrdiff_t col{0}; col < processed_image.cols; ++col)
        {
            for (ptrdiff_t el_r(row - median_kernel_sz/2); el_r <= row + median_kernel_sz/2; ++el_r)
                for (ptrdiff_t el_c(col - median_kernel_sz/2); el_c <= col + median_kernel_sz/2; ++el_c)
                {
  
                    window_elements_h.emplace_back(processed_image.at<cv::Vec3b>(get_index_inf(el_r, processed_image.rows),
                                                                            get_index_inf(el_c, processed_image.cols))[0]);
                    window_elements_s.emplace_back(processed_image.at<cv::Vec3b>(get_index_inf(el_r, processed_image.rows),
                                                                            get_index_inf(el_c, processed_image.cols))[1]);
                    window_elements_v.emplace_back(processed_image.at<cv::Vec3b>(get_index_inf(el_r, processed_image.rows),
                                                                            get_index_inf(el_c, processed_image.cols))[2]);
                }
            std::sort(window_elements_h.begin(), window_elements_h.end());
            std::sort(window_elements_s.begin(), window_elements_s.end());
            std::sort(window_elements_v.begin(), window_elements_v.end());

            processed_image.at<cv::Vec3b>(row, col)[0] = window_elements_h.at(window_elements_h.size()/2);
            processed_image.at<cv::Vec3b>(row, col)[1] = window_elements_s.at(window_elements_s.size()/2);
            processed_image.at<cv::Vec3b>(row, col)[2] = window_elements_v.at(window_elements_v.size()/2);


            window_elements_h.clear();
            window_elements_s.clear();
            window_elements_v.clear();

        }
    }
     
    cv::imshow("median", processed_image);
    cv::imwrite("../resources/median.jpeg", image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));

    // Box Filter
    // ----------
    image.copyTo(processed_image);
    cv::boxFilter(processed_image, processed_image, -1, cv::Size(3,3));
    cv::imshow("BoxFilter", processed_image);
    cv::imwrite("../resources/box.jpeg", image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));

    cv::imshow("Image", image);
    cv::waitKey();
   	
    return 0;
}
