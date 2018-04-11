#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>

using namespace cv;

int
main()
{
    cv::Mat image;
    cv::Mat equilized_image;
    cv::Mat rand_im;
    image = cv::imread("/Users/vorfolomeev/Desktop/container.jpg", 1);
    if (!image.data)
    {
        std::cout << "Failed to read\n";
        return 1;
    }

    cv::Mat gray_image;
    // Color converting function 
    // -------------------------
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    if (!gray_image.data)
    {
        std::cout << "Failed to convert color\n";
        return 1;
    }

    // Histogram 
    // ---------
    cv::equalizeHist(gray_image, equilized_image);
    
    // Here image will be separated in 3 channels b, g, r
    // ---------------------------------------------------
    std::vector<cv::Mat> bgr_chanels;
    cv::split(image, bgr_chanels);
    
    // Prepare settings for histogram calculation 
    // ------------------------------------------
    int hist_size = 256;

    float range[]           = {0, 256};
    const float *hist_range = {range};

    bool uniform    = true;
    bool acomulate  = false;

    cv::Mat b_hist, g_hist, r_hist;
    
    // Calculate histogram 
    // -------------------
    cv::calcHist(&bgr_chanels.at(0), 1, 0, cv::Mat(), 
                 b_hist, 1, &hist_size, &hist_range, 
                 uniform, acomulate);
    cv::calcHist(&bgr_chanels.at(1), 1, 0, cv::Mat(), 
                 g_hist, 1, &hist_size, &hist_range, 
                 uniform, acomulate);
    cv::calcHist(&bgr_chanels.at(2), 1, 0, cv::Mat(), 
                 r_hist, 1, &hist_size, &hist_range, 
                 uniform, acomulate);
    
    // Draw histogramm 
    // ---------------
    uint32_t hist_wight  = 512;
    uint32_t hist_height = 400;
    uint32_t bin_w       = cvRound((static_cast<double>(hist_wight / hist_size))); 

    cv::Mat hist_image(hist_height, hist_wight, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(b_hist, b_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(g_hist, g_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(r_hist, r_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (size_t i{0}; i < hist_size; ++i)
    {
        line(hist_image, Point( bin_w*(i-1), hist_height - cvRound(b_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_height - cvRound(b_hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
        line(hist_image, Point( bin_w*(i-1), hist_height - cvRound(g_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_height - cvRound(g_hist.at<float>(i)) ),
                       Scalar( 0, 255, 0), 2, 8, 0  );
         line(hist_image, Point( bin_w*(i-1), hist_height - cvRound(r_hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_height - cvRound(r_hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 2, 8, 0  );
    }

    // Dispaly images 
    // --------------
    cv::imshow("Colored", hist_image );
    cv::waitKey();

   	return 0;
}

