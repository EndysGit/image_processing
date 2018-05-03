#include <iostream>
#include "3dparty/FastNoise.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include "3dparty/tinyxml2/tinyxml2.h"

// noise type 
// seed 
// demension
//

int
main()
{
    constexpr size_t cx_rows{500};
    constexpr size_t cx_cols{500};

    tinyxml2::XMLDocument doc;
    doc.LoadFile("fast_n.xml");

    const char* title = doc.FirstChildElement( "FastNoise" )->FirstChildElement( "NoiseType" )->GetText();
    printf( "NoiseType: %s\n", title );

    doc.NewElement("kek");
    doc.NewText("new text");
    doc.NewComment("NewComment");
    doc.SaveFile("fast_n.xml");
/*
    
    cv::Mat image(cx_rows, cx_cols, CV_32FC1);
    cv::Mat image_one_more(cx_rows, cx_cols, CV_32FC1);
    cv::Mat image_check(cx_rows, cx_cols, CV_32FC1);
    FastNoise myNoise; // Create a FastNoise object
    FastNoise one_more;
    FastNoise check;

    myNoise.SetNoiseType(FastNoise::SimplexFractal); // Set the desired noise type
    myNoise.SetNoiseType(FastNoise::SimplexFractal);

    auto seed       = myNoise.GetSeed();
    auto type       = myNoise.GetNoiseType();
    auto interp     = myNoise.GetInterp();
    auto frequency  = myNoise.GetFrequency();

    std::cout << seed << ' ' << type << ' ' << interp << ' ' << frequency << '\n';  

    check.SetNoiseType(type);
    check.SetSeed(seed);
    check.SetInterp(interp);
    check.SetFrequency(frequency);
    for (int x = 0; x < cx_cols; x++)
       for (int y = 0; y < cx_rows; y++)
       {
           image.at<float>(x, y)          = myNoise.GetNoise(x, y);
           image_one_more.at<float>(x, y) = one_more.GetNoise(x, y);
           image_check.at<float>(x, y)    = check.GetNoise(x, y);
       }

    cv::imshow("Image", image);
    cv::imshow("Image one more", image_one_more);
    cv::imshow("Image check", image_check);

    check.SetNoiseType(one_more.GetNoiseType());
    check.SetSeed(one_more.GetSeed());
    check.SetInterp(one_more.GetInterp());
    check.SetFrequency(one_more.GetFrequency());

    for (int x = 0; x < cx_cols; x++)
       for (int y = 0; y < cx_rows; y++)
           image_check.at<float>(x, y)    = check.GetNoise(x, y);

    cv::imshow("Image check 2 ", image_check);
    cv::waitKey();
    */
   	return 0;
}
