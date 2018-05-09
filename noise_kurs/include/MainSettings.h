#ifndef FASTNOISE_MAINSETTINGS_HH
#define FASTNOISE_MAINSETTINGS_HH

#include "NoiseView.h"
#include "FractalSettings.h"
#include "CelluralSettings.h"

enum EGeneralSettings
{
    ID_NOISE_TYPE = 20,
    ID_SEED,
    ID_FREQUENCY,
    ID_INTERPOLATION
};

class MainControlPamel : public wxPanel
{
public:
    MainControlPamel(FastNoise &noise,  
                     wxWindow *parent, 
                     wxWindowID id,
                     const wxPoint &position = wxDefaultPosition, 
                     const wxSize &size = wxDefaultSize); 

    void SetFractalPanel(FractalSettingsPanel *panel);
    void SetCelluralPanel(CelluralSettingsPanel *panel);
private:
    void OnChoiceNoiseType(wxCommandEvent &event);
    void OnSeedEnter(wxCommandEvent &event);
    void OnFrequencyEnter(wxCommandEvent &event);
    void OnChoiceInterpolation(wxCommandEvent &event);

    FractalSettingsPanel *m_fractal_panel;
    CelluralSettingsPanel *m_cellural_panel;

    wxArrayString interpolation_type;
    wxArrayString noise_type;

    wxChoice *m_ch_noise_type;
    wxTextCtrl *m_tc_seed;
    wxTextCtrl *m_tc_frequency;
    wxChoice *m_ch_interpolation_type;
    
    FastNoise *m_noise;
    DECLARE_EVENT_TABLE()
};

#endif // FASTNOISE_MAINSETTINGS_HH
