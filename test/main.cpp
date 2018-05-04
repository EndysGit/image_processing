#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

void draw(cv::Mat &image, size_t color, size_t offsetx = 0, size_t offsety = 0)
{
    cv::rectangle(image, 
                  cv::Point(20 + offsetx, 20 + offsety), 
                  cv::Point(60 + offsetx, 60 + offsety), 
                  cv::Scalar(color, color, color), -1);

    cv::ellipse(image, 
                cv::Point(100 + offsetx, 40 + offsety), 
                cv::Size(30, 30), 
                0.0, 360.0, 0.0, 
                cv::Scalar(color / 2, color / 2, color / 2), -1);

    cv::Point points[1][3];
    points[0][0] = cv::Point(150 + offsetx, 60 + offsety);
    points[0][1] = cv::Point(190 + offsetx, 60 + offsety);
    points[0][2] = cv::Point(170 + offsetx, 20 + offsety);

    const cv::Point *ppt[1] = {points[0]};
    int npt[] = {3}; 
    cv::fillPoly(image, ppt, npt, 1, cv::Scalar(color / 4, color / 4, color / 4));
}
size_t 
get_index_inf(ptrdiff_t ind, size_t demnsion_size)
{
    return  (ind >= 0 && ind < demnsion_size) ?
         ind : abs(ind + static_cast<ptrdiff_t>(demnsion_size));
}

/*
Тест. Сделать серую картинку с разными фигурами,
квадрат - треугольник - круг, разный цвет (серый, белый, чёрный), 
разный фон того же цвета. Посчитать производные по разным направлениям, 
потом сделать картинку, где в hsv в канале яркости будет модуль градиента, а производные в двух других
*/

int
main()
{
    constexpr size_t cx_height{600};
    constexpr size_t cx_width{90};
    constexpr size_t cx_h{0};
    constexpr size_t cx_s{1};
    constexpr size_t cx_v{2};

    cv::Mat main_image(cx_width, cx_height, CV_8UC1);

    for(size_t row{0}; row < main_image.rows; ++row)
        for(size_t col{0}; col < main_image.cols; ++col)
            if (col >= 400)
                main_image.at<uint8_t>(row, col) = 255;
            else if (col >= 200)
                main_image.at<uint8_t>(row, col) = 70;

    draw(main_image, 240);
    draw(main_image, 240, 200);
    draw(main_image, 240, 400);

    cv::Mat processed_image(main_image.rows, main_image.cols, CV_32FC3);
    cv::cvtColor(processed_image, processed_image, CV_BGR2HSV);

    for(ptrdiff_t y{0}; y < main_image.rows; ++y)
    {
        for(ptrdiff_t x{0}; x < main_image.cols; ++x)
        {
            float dx = std::round(static_cast<float>(main_image.at<uint8_t>(y, get_index_inf(x + 1, main_image.cols))) / 2.0 - 
                                  static_cast<float>(main_image.at<uint8_t>(y, get_index_inf(x - 1, main_image.cols))) / 2.0);

            float dy = std::round(static_cast<float>(main_image.at<uint8_t>(get_index_inf(y - 1, main_image.rows), x)) / 2.0 -
                                  static_cast<float>(main_image.at<uint8_t>(get_index_inf(y + 1, main_image.rows), x)) / 2.0);

            dx += 128;
            dy += 128;

            processed_image.at<cv::Vec3f>(y, x)[cx_h] =  sqrt(dx * dx + dy * dy) / sqrt(2) / 180;
            processed_image.at<cv::Vec3f>(y, x)[cx_s] =  dy /255;
            processed_image.at<cv::Vec3f>(y, x)[cx_v] =  dx /255; 
        }
    }

    cv::cvtColor(processed_image, processed_image, CV_HSV2RGB);

    cv::imshow("main_image", main_image);
    cv::imwrite("../resources/src_image.jpeg", main_image, std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));

    cv::imshow("processed_image", processed_image);
    processed_image *= 255;
    cv::imwrite("../resources/proccesed_image.jpeg", processed_image,  std::vector<int>({CV_IMWRITE_JPEG_QUALITY, 100}));

    cv::waitKey();

   	return 0;
}
