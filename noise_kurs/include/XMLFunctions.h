#ifndef FASTNOISE_XMLFUNCTIONS_HH
#define FASTNOISE_XMLFUNCTIONS_HH

#include <string>
#include "3dparty/tinyxml2/include/tinyxml2.h"

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

    tinyxml2::XMLElement *interp = doc.NewElement(c_interp.c_str());
    interp->SetText(interpolation_i);
    pRoot->InsertEndChild(interp);

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

    const char* interp = doc.FirstChildElement(c_fast_noise.c_str())->FirstChildElement(c_interp.c_str())->GetText();
    interpolation_i = std::atoi(interp);

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

#endif // FASTNOISE_XMLFUNCTIONS_HH
