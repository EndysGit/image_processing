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
const std::string c_fast_noise              = "FastNoise";
const std::string c_noise_type              = "NoiseType";
const std::string c_seed                    = "Seed";
const std::string c_frequency               = "Frequency";
const std::string c_interp                  = "Interpolation";
const std::string c_fractal_type            = "FractalType";
const std::string c_fractal_octaves         = "FractalOctaves";
const std::string c_fractal_lacunarity      = "FractalLacunarity";
const std::string c_fractal_gain            = "FractalGain";
const std::string c_cellural_dist_function  = "CelluralDistanceFunction";
const std::string c_cellural_return_type    = "CelluralReturnType";

void 
save_to_xml(const std::string &path,
            int noise_type_i, 
            int seed_i, 
            double frequency_d, 
            int interpolation_i, 
            int fractal_type_i,
            int fractal_octave_i, 
            double fractal_lacunarity_d, 
            double fractal_gain_d, 
            int cellural_return_type_i, 
            int cellural_distance_function_i)
{

    tinyxml2::XMLDocument doc;

    tinyxml2::XMLNode *pRoot = doc.NewElement(c_fast_noise.c_str());
    doc.InsertFirstChild(pRoot);
    
    tinyxml2::XMLElement *noise_type = doc.NewElement(c_noise_type.c_str()); 
    noise_type->SetText(noise_type_i);
    pRoot->InsertEndChild(noise_type);

    tinyxml2::XMLElement *seed = doc.NewElement(c_seed.c_str()); 
    seed->SetText(seed_i);
    pRoot->InsertEndChild(seed);

    tinyxml2::XMLElement *frequency = doc.NewElement(c_frequency.c_str()); 
    frequency->SetText(frequency_d);
    pRoot->InsertEndChild(frequency);

    tinyxml2::XMLElement *interpolation = doc.NewElement(c_interp.c_str()); 
    interpolation->SetText(interpolation_i);
    pRoot->InsertEndChild(interpolation);

    tinyxml2::XMLElement *fractal_type = doc.NewElement(c_fractal_type.c_str()); 
    fractal_type->SetText(fractal_type_i);
    pRoot->InsertEndChild(fractal_type);

    tinyxml2::XMLElement *fractal_octave = doc.NewElement(c_fractal_octaves.c_str()); 
    fractal_octave->SetText(fractal_octave_i);
    pRoot->InsertEndChild(fractal_octave);

    tinyxml2::XMLElement *fractal_lacunarity = doc.NewElement(c_fractal_lacunarity.c_str()); 
    fractal_lacunarity->SetText(fractal_lacunarity_d);
    pRoot->InsertEndChild(fractal_lacunarity);

    tinyxml2::XMLElement *fractal_gain = doc.NewElement(c_fractal_gain.c_str());
    fractal_gain->SetText(fractal_gain_d);
    pRoot->InsertEndChild(fractal_gain);

    tinyxml2::XMLElement *cellural_distance_function = doc.NewElement(c_cellural_dist_function.c_str()); 
    cellural_distance_function->SetText(cellural_distance_function_i);
    pRoot->InsertEndChild(cellural_distance_function);

    tinyxml2::XMLElement *cellural_return_type = doc.NewElement(c_cellural_return_type.c_str()); 
    cellural_return_type->SetText(cellural_return_type_i);
    pRoot->InsertEndChild(cellural_return_type);

    doc.SaveFile(path.c_str());
}

void open_from_xml(const std::string &path,
                   int &noise_type_i, 
                   int &seed_i, 
                   double &frequency_d, 
                   int &interpolation_i, 
                   int &fractal_type_i,
                   int &fractal_octave_i, 
                   double &fractal_lacunarity_d, 
                   double &fractal_gain_d,
                   int &cellural_return_type_i, 
                   int &cellural_distance_function_i)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());

    const char* noise_type = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_noise_type.c_str())->GetText();
    noise_type_i = std::atoi(noise_type);

    const char* seed = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_seed.c_str())->GetText();
    seed_i = std::atoi(seed);
    
    const char* frequency = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_frequency.c_str())->GetText();
    frequency_d = std::atof(frequency);
    
    const char* interpolation = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_interp.c_str())->GetText();
    interpolation_i = std::atoi(interpolation);
    
    const char* fractal_type  = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_fractal_type.c_str())->GetText();
    fractal_type_i = std::atoi(fractal_type);
    
    const char* fractal_octave = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_fractal_octaves.c_str())->GetText();
    fractal_octave_i = std::atoi(fractal_octave);
    
    const char* fractal_lacunarity = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_fractal_lacunarity.c_str())->GetText();
    fractal_lacunarity_d = std::atof(fractal_lacunarity);
    
    const char* fractal_gain = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_fractal_gain.c_str())->GetText();
    fractal_gain_d = std::atof(fractal_gain);
    
    const char* cellural_return_type = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_cellural_return_type.c_str())->GetText();
    cellural_return_type_i = std::atoi(cellural_return_type);
    
    const char* cellural_distance_function = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_cellural_dist_function.c_str())->GetText();
    cellural_distance_function_i = std::atoi(cellural_distance_function);
}

int
main()
{
    constexpr size_t cx_rows{500};
    constexpr size_t cx_cols{500};

    tinyxml2::XMLDocument doc;
    doc.LoadFile("fast_n.xml");

    FastNoise myNoise; // Create a FastNoise object
    myNoise.SetNoiseType(FastNoise::SimplexFractal); // Set the desired noise type
 
    save_to_xml("fast.xml", 
                myNoise.GetNoiseType(), 
                myNoise.GetSeed(), 
                myNoise.GetFrequency(), 
                myNoise.GetInterp(),
                myNoise.GetFractalType(), 
                myNoise.GetFractalOctaves(),
                myNoise.GetFractalLacunarity(),
                myNoise.GetFractalGain(),
                myNoise.GetCellularReturnType(),
                myNoise.GetCellularDistanceFunction());

    int noise_type_i; 
    int seed_i;
    double frequency_d; 
    int interpolation_i; 
    int fractal_type_i;
    int fractal_octave_i; 
    double fractal_lacunarity_d; 
    double fractal_gain_d;
    int cellural_return_type_i; 
    int cellural_distance_function_i;
    open_from_xml("fast.xml", 
                   noise_type_i, 
                   seed_i, 
                   frequency_d, 
                   interpolation_i, 
                   fractal_type_i, 
                   fractal_octave_i, 
                   fractal_lacunarity_d, 
                   fractal_gain_d, 
                   cellural_return_type_i, 
                   cellural_distance_function_i);


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
