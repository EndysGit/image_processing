#include <iostream>
#include "3dparty/FastNoise.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

#define CVUI_IMPLEMENTATION
#include "3dparty/cvui.h"


// noise type 
// seed 
// demension
//

#define WINDOW_NAME	"Complex layout"

void group(cv::Mat& frame, int x, int y, int width, int height) {
	int padding = 5, w = (width - padding) / 4, h = (height - 15 - padding) / 2;
	cv::Point pos(x + padding, y + 5);

	cvui::text(frame, pos.x, pos.y, "Group title");
	pos.y += 15;

	cvui::window(frame, pos.x, pos.y, width - padding * 2, h - padding, "Something");
	cvui::rect(frame, pos.x + 2, pos.y + 20, width - padding * 2 - 5, h - padding - 20, 0xff0000);
	pos.y += h;
;
}


int
main()
{
    constexpr size_t cx_rows{500};
    constexpr size_t cx_cols{500};


	cv::Mat frame = cv::Mat(cx_rows , cx_cols, CV_8UC3);
    cv::Mat src_image = cv::imread("shiro.png");
    cv::Mat work_image;

    cv::Size sz(src_image.rows / 2, src_image.cols / 2);
    cv::resize(src_image, work_image, sz);

	// Init cvui and tell it to create a OpenCV window, i.e. cv::namedWindow(WINDOW_NAME).
	cvui::init(WINDOW_NAME);

	while (true)
    {
		frame = cv::Scalar(100, 100, 100);

        cvui::image(frame, 10, 10, work_image);
        

		cvui::update();

		// Show everything on the screen
		cv::imshow(WINDOW_NAME, frame);
		
		// Check if ESC key was pressed
		if (cv::waitKey(20) == 27) {
			break;
		}
	}
	

	
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
