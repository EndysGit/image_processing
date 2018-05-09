#include "MainSettings.h"

BEGIN_EVENT_TABLE(MainControlPamel, wxPanel)
    EVT_CHOICE(ID_NOISE_TYPE, MainControlPamel::OnChoiceNoiseType)
    //EVT_TEXT_ENTER(ID_SEED, MainControlPamel::OnSeedEnter)
    EVT_TEXT(ID_SEED, MainControlPamel::OnSeedEnter)
    //EVT_TEXT_ENTER(ID_FREQUENCY, MainControlPamel::OnFrequencyEnter)
    EVT_TEXT(ID_FREQUENCY, MainControlPamel::OnFrequencyEnter)
    EVT_CHOICE(ID_INTERPOLATION, MainControlPamel::OnChoiceInterpolation)
END_EVENT_TABLE();

MainControlPamel::MainControlPamel(FastNoise &noise,  
                     wxWindow *parent, 
                     wxWindowID id,
                     const wxPoint &position, 
                     const wxSize &size) :
        wxPanel(parent, id, position, size)
    {
        m_noise = &noise;
        this->SetBackgroundColour(wxColour(175, 175, 175));
        
        wxSizerFlags flags = wxSizerFlags(0).Align(1).Border(wxALL, 1);

        wxStaticBoxSizer *main_sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Main settings");
        wxGridSizer *gs = new wxGridSizer(2, 5, 5);
        
        // Noise type
        noise_type.Add("Value");
        noise_type.Add("ValueFractal");
        noise_type.Add("Perlin");
        noise_type.Add("PerlinFractal");
        noise_type.Add("Simplex");
        noise_type.Add("SimplexFractal");
        noise_type.Add("Cellular");
        noise_type.Add("WhiteNoise");
        noise_type.Add("Cubic");
        noise_type.Add("CubicFractal");

        m_ch_noise_type = new wxChoice(this, ID_NOISE_TYPE, wxDefaultPosition, wxDefaultSize, noise_type);
        m_noise->SetNoiseType(FastNoise::NoiseType::Value);

        gs->Add(new wxStaticText(this, wxID_ANY, "Noise type:"),  flags);
        gs->Add(m_ch_noise_type, flags);

        // Noise seed
        gs->Add(new wxStaticText(this, wxID_ANY, "Seed:"), flags);
        
        m_tc_seed = new wxTextCtrl(this, ID_SEED, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_seed << 1337;
        m_noise->SetSeed(1337);

        gs->Add(m_tc_seed, flags);

        // Noise Frequency
        gs->Add(new wxStaticText(this, wxID_ANY, "Frequency:"), flags);

        m_tc_frequency = new wxTextCtrl(this, ID_FREQUENCY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_frequency << 0.02222;
        m_noise->SetFrequency(0.02222);

        gs->Add(m_tc_frequency,  flags);
       
        // Noise Interpolation
        interpolation_type.Add("Linear");
        interpolation_type.Add("Hermite");
        interpolation_type.Add("Quintic");
        
        m_ch_interpolation_type = new wxChoice(this, ID_INTERPOLATION, wxDefaultPosition, wxDefaultSize, interpolation_type);
        m_noise->SetInterp(FastNoise::Interp::Linear);

        // Noise INterpolation 
        gs->Add(new wxStaticText(this, wxID_ANY, "Interpolation:"), flags);
        gs->Add(m_ch_interpolation_type, flags);
    
        main_sizer->Add(gs);

        SetSizerAndFit(main_sizer);
        
    }

void 
MainControlPamel::SetFractalPanel(FractalSettingsPanel *panel)
{
    m_fractal_panel = panel;
    m_fractal_panel->Disable();
}

void 
MainControlPamel::SetCelluralPanel(CelluralSettingsPanel *panel)
{
    m_cellural_panel = panel;
    m_cellural_panel->Disable();
}

void 
MainControlPamel::OnChoiceNoiseType(wxCommandEvent &event)
{
    int noise_type_i = m_ch_noise_type->GetCurrentSelection();
    switch (noise_type_i)
    {
        case 1: case 3: case 5: case 7: case 9:
            m_fractal_panel->Enable();
            m_cellural_panel->Disable();
            m_ch_interpolation_type->Disable();
            break;
        case 6:
            m_fractal_panel->Disable();
            m_cellural_panel->Enable();
            break;
        case 0: case 2: case 4:  case 8:
            if (noise_type_i == 0 || noise_type_i == 2)
                m_ch_interpolation_type->Enable();
            else 
            {
                m_ch_interpolation_type->Disable();
                m_noise->SetInterp(FastNoise::Quintic);
            }
            m_fractal_panel->Disable();
            m_cellural_panel->Disable();
            break;
    }
    
    m_noise->SetNoiseType(static_cast<FastNoise::NoiseType>(noise_type_i)); 
}

void 
MainControlPamel::OnSeedEnter(wxCommandEvent &event)
{
    int seed;

    if (m_tc_seed->GetLineText(0).IsNumber())
    {
        seed = wxAtoi(m_tc_seed->GetLineText(0));
        m_noise->SetSeed(seed);
    }
    else 
        wxMessageBox("Wrong format, please type integer!");
}

void 
MainControlPamel::OnFrequencyEnter(wxCommandEvent &event)
{
    double frequency;
    
    if (m_tc_frequency->GetLineText(0).ToDouble(&frequency))
        m_noise->SetFrequency(static_cast<FN_DECIMAL>(frequency));
    else 
        wxMessageBox("Wrong format, please type integer!");
}

void 
MainControlPamel::OnChoiceInterpolation(wxCommandEvent &event)
{
    int interp_type_i = m_ch_interpolation_type->GetCurrentSelection();   
    m_noise->SetInterp(static_cast<FastNoise::Interp>(interp_type_i));
}
