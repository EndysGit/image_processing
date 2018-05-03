#ifndef FASTNOISE_MAINFRAIM_HH
#define FASTNOISE_MAINFRAIM_HH

#include <map>
#include <array>
#include <wx/wxprec.h>
#include "3dparty/FastNoise.h" 
#include "MainFrame.h"
#include "NoiseView.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

constexpr size_t parameters_number{0};
static const std::array<const std::string, parameters_number> param = {"seed", };  

FastNoise GetNoise(const std::map<wxString, FN_DECIMAL> &noise_parametrs)
{
    FastNoise result_noise;
    result_noise.SetSeed(noise_parametrs.at("seed"));
    result_noise.SetInterp(static_cast<FastNoise::Interp>(noise_parametrs.at("interp")));
    result_noise.SetFrequency(noise_parametrs.at("frequency"));
    result_noise.SetNoiseType(static_cast<FastNoise::NoiseType>(noise_parametrs.at("noise_type")));
    result_noise.SetFractalType(static_cast<FastNoise::FractalType>(noise_parametrs.at("fractal_type")));
    result_noise.SetFractalGain(noise_parametrs.at("fractal_gain"));
    result_noise.SetFractalOctaves(noise_parametrs.at("fractal_octaves"));
    result_noise.SetFractalLacunarity(noise_parametrs.at("fractal_lacunarity"));

    return result_noise;
}

std::map<wxString, int> GetParameters(const FastNoise &noise) 
{
    std::map<wxString, int> noise_parametrs;

    return noise_parametrs;
}

void json2map(const std::string &jsoni, std::map<wxString, int> &noise_parametrs)
{

}

void map2json(const std::map<wxString, int> &noise_parametrs, std::string &json)
{

}


class NoiseApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Main entery point
wxIMPLEMENT_APP(NoiseApp);

bool NoiseApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);

   return true;
}

#endif // FASTNOISE_MAINFRAME_HH
