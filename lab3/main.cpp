#include <iostream>
#include <array>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>
#include <cmath>

/* Сделать выравнивание яркости (серая картинка), выше и ниже определенного 
 * диапазона пиксели отсекаются, оставшаяся часть линейно растягивается от 0 до 255.
 * */
int
main()
{
    constexpr uint16_t range{255}; 
    std::array<double, range> hist;
    hist.fill(0.0000);

    cv::Mat image;
    cv::imread("leo.jpg", CV_8UC4).copyTo(image);    
    cv::cvtColor(image, image, CV_BGR2GRAY);
    
    cv::Mat processed_image;
    image.copyTo(processed_image);

    std::for_each(processed_image.begin<uint8_t>(), 
                  processed_image.end<uint8_t>(), 
                  [&](uint8_t pix)
                  { 
                    hist.at(pix) += 1.0; 
                  });

    double hist_max{*(std::max_element(hist.cbegin(), hist.cend()))};

    std::cout << "hist max = " << hist_max << '\n';
    std::for_each(hist.begin(), 
                  hist.end(), 
                  [hist_max, range](double &val) 
                  { 
                    val /= hist_max; 
                  });

    cv::Mat hist_image(range, range, CV_8UC1);   
    for(ptrdiff_t row{0}; row < hist.size() - 1; ++row)
    {
        cv::line(hist_image, 
                 cv::Point(row, hist_image.rows - static_cast<ptrdiff_t>(std::round(range * hist.at(row)))), 
                 cv::Point(row + 1, hist_image.rows - static_cast<ptrdiff_t>( std::round(range * hist.at(row + 1)))),
                 255, 2, 8, 0);
    }

    double left{hist.at(25)};
    double right{hist.at(hist.size() - 25)};
    std::for_each(processed_image.begin<uint8_t>(), 
                  processed_image.end<uint8_t>(),
                  [left, right](uint8_t &pix)
                  { 
                    double new_left = (static_cast<double>(pix)/static_cast<double>(range) - left) ; 
                    double new_right = ((new_left <= 0.0000) ? 0 : new_left) * (left + 1.0 - right);
                    double result = (new_right >= right ? 1 : new_right) * 255;
                    pix = static_cast<uint8_t>(result);
                  }
                 );

    cv::imshow("hist image", hist_image); 

    hist.fill(0.000000);
     std::for_each(hist_image.begin<uint8_t>(), 
                  hist_image.end<uint8_t>(), 
                  [&](uint8_t &pix)
                  { 
                    pix = 0;
                  });


    std::for_each(processed_image.begin<uint8_t>(), 
                  processed_image.end<uint8_t>(), 
                  [&](uint8_t pix)
                  { 
                    hist.at(pix) += 1.0; 
                  });

    hist_max = *(std::max_element(hist.cbegin(), hist.cend()));

    std::cout << "hist max = " << hist_max << '\n';
    std::for_each(hist.begin(), 
                  hist.end(), 
                  [hist_max, range](double &val) 
                  { 
                    val /= hist_max; 
                  });

    for(ptrdiff_t row{0}; row < hist.size() - 1; ++row)
    {
        cv::line(hist_image, 
                 cv::Point(row, hist_image.rows - static_cast<ptrdiff_t>(std::round(range * hist.at(row)))), 
                 cv::Point(row + 1, hist_image.rows - static_cast<ptrdiff_t>( std::round(range * hist.at(row + 1)))),
                 255, 2, 8, 0);
    }

    cv::imshow("hist_processed", hist_image);

    cv::imshow("processed_image", processed_image);
    cv::imshow("image", image);
    cv::waitKey();
    return 0;
}
