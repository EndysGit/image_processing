#include "FractalSettings.h"

BEGIN_EVENT_TABLE(FractalSettingsPanel, wxPanel)
    EVT_CHOICE(ID_FRACTAL_TYPE, FractalSettingsPanel::OnChoiceFractalType)
    EVT_TEXT(ID_FRACTAL_OCTAVES, FractalSettingsPanel::OnOctavesEnter)
    EVT_TEXT(ID_FRACTAL_LACUNARITY, FractalSettingsPanel::OnLacunarityEnter)
    EVT_TEXT(ID_FRACTAL_GAIN, FractalSettingsPanel::OnGainEnter)
END_EVENT_TABLE();

FractalSettingsPanel::FractalSettingsPanel(FastNoise &noise, 
                         wxWindow *parent, 
                         wxWindowID id, 
                         const wxPoint &position, 
                         const wxSize &size)
        : wxPanel(parent, id, position, size)
    {
        m_noise = &noise;
       
        this->SetBackgroundColour(wxColour(175, 175, 175));

        wxSizerFlags flags = wxSizerFlags(0).Center().Border(wxALL, 1);

        wxStaticBoxSizer *main_sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Fractal Settings");
    
        wxArrayString str;
        str.Add("FBM");
        str.Add("Billow");
        str.Add("RigidMulti");
        m_ch_fractal_type = new wxChoice(this, ID_FRACTAL_TYPE, wxDefaultPosition, wxDefaultSize,str);
        m_noise->SetFractalType(FastNoise::FBM);

        wxGridSizer *gs = new wxGridSizer(2, 5, 5);
        // Fractal type
        gs->Add(new wxStaticText(this, wxID_ANY, "Fractal type:"),  flags);
        gs->Add(m_ch_fractal_type, flags);
        // Fractal octaves
        gs->Add(new wxStaticText(this, wxID_ANY, "Octaves:"), flags);

        m_tc_octaves = new wxTextCtrl(this, ID_FRACTAL_OCTAVES, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_octaves << 5;
        m_noise->SetFractalOctaves(5);

        gs->Add(m_tc_octaves,  flags);
        // Fractal lacunarity
        gs->Add(new wxStaticText(this, wxID_ANY, "Lacunarity:"), flags);

        m_tc_lacunarity = new wxTextCtrl(this, ID_FRACTAL_LACUNARITY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_lacunarity << 2.0;
        m_noise->SetFractalLacunarity(2.0);

        gs->Add(m_tc_lacunarity,  flags);
        // Fractal gain
        gs->Add(new wxStaticText(this, wxID_ANY, "Gain:"), flags);

        m_tc_gain = new wxTextCtrl(this, ID_FRACTAL_GAIN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_gain << 0.5;
        m_noise->SetFractalGain(0.5);

        gs->Add(m_tc_gain, flags);
    
        main_sizer->Add(gs);

        SetSizerAndFit(main_sizer);
    }

void
FractalSettingsPanel::OnChoiceFractalType(wxCommandEvent &event)
{
    int fractal_type_i = m_ch_fractal_type->GetCurrentSelection();
    m_noise->SetFractalType(static_cast<FastNoise::FractalType>(fractal_type_i));
}

void
FractalSettingsPanel::OnOctavesEnter(wxCommandEvent &event)
{
    int octave;
    if (m_tc_octaves->GetLineText(0).IsNumber())
    {
        octave = wxAtoi(m_tc_octaves->GetLineText(0));
        m_noise->SetFractalOctaves(octave);
    }
    else
        wxMessageBox("Wrong format, please type integer!");

}

void
FractalSettingsPanel::OnLacunarityEnter(wxCommandEvent &event)
{
    double lacunarity;

    if (m_tc_lacunarity->GetLineText(0).ToDouble(&lacunarity))
        m_noise->SetFractalLacunarity(static_cast<FN_DECIMAL>(lacunarity));
    else
        wxMessageBox("Wrong format, please type integer!");
}

void
FractalSettingsPanel::OnGainEnter(wxCommandEvent &event)
{
    double gain;

    if (m_tc_gain->GetLineText(0).ToDouble(&gain))
        m_noise->SetFractalGain(static_cast<FN_DECIMAL>(gain));
    else
        wxMessageBox("Wrong format, please type integer!");
}
