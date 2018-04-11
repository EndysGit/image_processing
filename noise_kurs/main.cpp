#include <iostream>
#include "FastNoise.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>

using namespace cv;

int
main()
{
    constexpr size_t rows{800};
    constexpr size_t cols{800};

    cv::Mat image(rows, cols, CV_32FC1);
    FastNoise myNoise; // Create a FastNoise object
    myNoise.SetNoiseType(FastNoise::SimplexFractal); // Set the desired noise type

    // 2D heightmap to create terrain

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            image.at<float>(x, y) = myNoise.GetNoise(x,y);
        }
    }
    
    cv::imshow("Image", image);
    cv::waitKey();

   	return 0;
}

