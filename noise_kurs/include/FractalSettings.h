#ifndef FASTNOISE_FRACTTALSETTINGS_HH
#define FASTNOISE_FRACTTALSETTINGS_HH

#include "MasterHeader.h"

enum EFractalSettings
{
    ID_FRACTAL_TYPE = 10,
    ID_FRACTAL_OCTAVES,
    ID_FRACTAL_LACUNARITY,
    ID_FRACTAL_GAIN
};

class FractalSettingsPanel : public wxPanel
{
public:
    FractalSettingsPanel(FastNoise &noise, 
                         wxWindow *parent, 
                         wxWindowID id, 
                         const wxPoint &position = wxDefaultPosition, 
                         const wxSize &size = wxDefaultSize);
private:
    void OnChoiceFractalType(wxCommandEvent &event);
    void OnOctavesEnter(wxCommandEvent &event);
    void OnLacunarityEnter(wxCommandEvent &event);
    void OnGainEnter(wxCommandEvent &event);
    
    wxChoice *m_ch_fractal_type;
    wxTextCtrl *m_tc_octaves;
    wxTextCtrl *m_tc_lacunarity;
    wxTextCtrl *m_tc_gain;

    FastNoise *m_noise;
    DECLARE_EVENT_TABLE()
};

#endif // FASTNOISE_FRACTALSETTINGS_HH
