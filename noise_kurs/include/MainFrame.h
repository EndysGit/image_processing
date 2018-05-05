#ifndef NOISE_MAINFRAME_HH
#define NOISE_MAINFRAME_HH

#include <wx-3.1/wx/frame.h>
#include <wx-3.1/wx/wfstream.h>
#include <wx-3.1/wx/choice.h>
#include <wx-3.1/wx/filedlg.h>
#include <wx-3.1/wx/textctrl.h>
#include <wx-3.1/wx/sizer.h>
#include <wx-3.1/wx/stattext.h>
#include <wx-3.1/wx/flags.h>
#include <wx-3.1/wx/msgdlg.h>
#include <wx-3.1/wx/log.h>
#include <wx-3.1/wx/menu.h>
#include <wx-3.1/wx/time.h>
#include <wx-3.1/wx/button.h>
#include <wx-3.1/wx/checkbox.h>
#include "NoiseView.h"
#include "XMLFunctions.h"

enum EFractalSettings
{
    ID_FRACTAL_TYPE = 10,
    ID_FRACTAL_OCTAVES,
    ID_FRACTAL_LACUNARITY,
    ID_FRACTAL_GAIN
};

enum EGeneralSettings
{
    ID_NOISE_TYPE = 20,
    ID_SEED,
    ID_FREQUENCY,
    ID_INTERPOLATION
};

enum ECelularSettings
{
    ID_DISTANCE_FUNCTION = 30,
    ID_RETURN_TYPE
};

class FractalSettingsPanel : public wxPanel
{
public:
    FractalSettingsPanel(FastNoise &noise, 
                         wxWindow *parent, 
                         wxWindowID id, 
                         const wxPoint &position = wxDefaultPosition, 
                         const wxSize &size = wxDefaultSize )
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

BEGIN_EVENT_TABLE(FractalSettingsPanel, wxPanel)
    EVT_CHOICE(ID_FRACTAL_TYPE, FractalSettingsPanel::OnChoiceFractalType)
    EVT_TEXT(ID_FRACTAL_OCTAVES, FractalSettingsPanel::OnOctavesEnter)
    EVT_TEXT(ID_FRACTAL_LACUNARITY, FractalSettingsPanel::OnLacunarityEnter)
    EVT_TEXT(ID_FRACTAL_GAIN, FractalSettingsPanel::OnGainEnter)
END_EVENT_TABLE();

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
class CelluralSettingsPanel : public wxPanel
{
public:
    CelluralSettingsPanel(FastNoise &noise, 
                          wxWindow *parent, 
                          wxWindowID id, 
                          const wxPoint &position = wxDefaultPosition, 
                          const wxSize &size = wxDefaultSize) 
        : wxPanel(parent, id, position, size)
    {
        m_noise = &noise;
        
        this->SetBackgroundColour(wxColour(175, 175, 175));
    
        wxSizerFlags flags =  wxSizerFlags(0).Center().Border(wxALL, 1);

        wxStaticBoxSizer *main_sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Fractal Settings");
    
        wxArrayString cell_returm_type;
        cell_returm_type.Add("CellValue");
        cell_returm_type.Add("NoiseLookup");
        cell_returm_type.Add("Distance");
        cell_returm_type.Add("Distance2");
        cell_returm_type.Add("Distance2Add");
        cell_returm_type.Add("Distance2Sub");
        cell_returm_type.Add("Distance2Mul");
        cell_returm_type.Add("Distance2Div");

        m_ch_cell_return_type = new wxChoice(this, ID_RETURN_TYPE, wxDefaultPosition, wxDefaultSize, cell_returm_type);
        m_noise->SetCellularReturnType(FastNoise::CellularReturnType::CellValue);

        wxGridSizer *gs = new wxGridSizer(2, 5, 5);

        // Return  type
        gs->Add(new wxStaticText(this, wxID_ANY, "Return type:"),  flags);
        gs->Add(m_ch_cell_return_type, flags);

        // Distance function type
        wxArrayString distance_funciton_type;
        distance_funciton_type.Add("Euclidean");
        distance_funciton_type.Add("Manhattan");
        distance_funciton_type.Add("Natural");

        m_ch_distance_function_type = new wxChoice(this, ID_DISTANCE_FUNCTION, wxDefaultPosition, wxDefaultSize, distance_funciton_type);
        m_noise->SetCellularDistanceFunction(FastNoise::CellularDistanceFunction::Euclidean);

        gs->Add(new wxStaticText(this, wxID_ANY, "Distance function:"), flags);
        gs->Add(m_ch_distance_function_type, flags);
    
        main_sizer->Add(gs);

        SetSizerAndFit(main_sizer);
    }
private:
    void OnChoiceReturnType(wxCommandEvent &event);
    void OnChoiceDistanceFunction(wxCommandEvent &event);
    
    wxChoice *m_ch_cell_return_type;
    wxChoice *m_ch_distance_function_type;

    FastNoise *m_noise;
    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(CelluralSettingsPanel, wxPanel)
    EVT_CHOICE(ID_RETURN_TYPE, CelluralSettingsPanel::OnChoiceReturnType)
    EVT_CHOICE(ID_DISTANCE_FUNCTION, CelluralSettingsPanel::OnChoiceDistanceFunction)
END_EVENT_TABLE();

void 
CelluralSettingsPanel::OnChoiceReturnType(wxCommandEvent &event)
{
    int return_type_i = m_ch_cell_return_type->GetCurrentSelection();
    m_noise->SetCellularReturnType(static_cast<FastNoise::CellularReturnType>(return_type_i));
}

void 
CelluralSettingsPanel::OnChoiceDistanceFunction(wxCommandEvent &event)
{
   int dist_func__type_i = m_ch_distance_function_type->GetCurrentSelection();
   m_noise->SetCellularDistanceFunction(static_cast<FastNoise::CellularDistanceFunction>(dist_func__type_i));
}

class MainControlPamel : public wxPanel
{
public:
    MainControlPamel(FastNoise &noise,  
                     wxWindow *parent, 
                     wxWindowID id,
                     const wxPoint &position = wxDefaultPosition, 
                     const wxSize &size = wxDefaultSize) :
        wxPanel(parent, id, position, size)
    {
        m_noise = &noise;
        this->SetBackgroundColour(wxColour(175, 175, 175));
        
        wxSizerFlags flags = wxSizerFlags(0).Center().Border(wxALL, 1);

        wxStaticBoxSizer *main_sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Main settings");

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

        wxGridSizer *gs = new wxGridSizer(2, 5, 5);
        // Noise type
        gs->Add(new wxStaticText(this, wxID_ANY, "Noise type:"),  flags);
        gs->Add(m_ch_noise_type, flags);
        // Noise seed
        gs->Add(new wxStaticText(this, wxID_ANY, "Seed:"), flags);
        
        m_tc_seed = new wxTextCtrl(this, ID_SEED, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_seed << 1337;
        m_noise->SetSeed(1337);

        gs->Add(m_tc_seed, flags);
        // Noise Frequenc
        gs->Add(new wxStaticText(this, wxID_ANY, "Frequency:"), flags);

        m_tc_frequency = new wxTextCtrl(this, ID_FREQUENCY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        *m_tc_frequency << 0.02;
        m_noise->SetFrequency(0.02);

        gs->Add(m_tc_frequency,  flags);
       
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

    void SetFractalPanel(FractalSettingsPanel *panel)
    {
        m_fractal_panel = panel;
        m_fractal_panel->Disable();
    }
    void SetCelluralPanel(CelluralSettingsPanel *panel)
    {
        m_cellural_panel = panel;
        m_cellural_panel->Disable();
    }
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

BEGIN_EVENT_TABLE(MainControlPamel, wxPanel)
    EVT_CHOICE(ID_NOISE_TYPE, MainControlPamel::OnChoiceNoiseType)
    EVT_TEXT_ENTER(ID_SEED, MainControlPamel::OnSeedEnter)
    EVT_TEXT(ID_SEED, MainControlPamel::OnSeedEnter)
    EVT_TEXT_ENTER(ID_FREQUENCY, MainControlPamel::OnFrequencyEnter)
    EVT_TEXT(ID_FREQUENCY, MainControlPamel::OnFrequencyEnter)
    EVT_CHOICE(ID_INTERPOLATION, MainControlPamel::OnChoiceInterpolation)
END_EVENT_TABLE();

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
        m_noise->SetSeed(static_cast<FN_DECIMAL>(frequency));
    else 
        wxMessageBox("Wrong format, please type integer!");

}

void 
MainControlPamel::OnChoiceInterpolation(wxCommandEvent &event)
{
    int interp_type_i = m_ch_interpolation_type->GetCurrentSelection();   
    m_noise->SetInterp(static_cast<FastNoise::Interp>(interp_type_i));
}

class MainFrame : public wxFrame
{
public:
    MainFrame();
private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnButtonGenerate(wxCommandEvent &event);
    void OnButtonSave(wxCommandEvent &event);
    void OnButtonOpen(wxCommandEvent &event);

    FastNoise *m_noise;

    NoieseView *m_noise_view;
    wxPanel *m_settings_panel;

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Hello = 1,
    ID_B_GENERATE,
    ID_B_SAVE,
    ID_B_OPEN,
    ID_NOISE_VIEW
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(ID_B_GENERATE, MainFrame::OnButtonGenerate)
    EVT_BUTTON(ID_B_SAVE, MainFrame::OnButtonSave)
    EVT_BUTTON(ID_B_OPEN, MainFrame::OnButtonOpen)
END_EVENT_TABLE();

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "FastNoise") 
{
    m_noise = new FastNoise();
    wxFlexGridSizer *sz = new wxFlexGridSizer(2, 5, 5);

    m_settings_panel = new wxPanel(this, wxID_ANY);
    m_settings_panel->SetBackgroundColour(wxColour(200, 200, 200));

    wxStaticBoxSizer *sizer_panel = new wxStaticBoxSizer(wxVERTICAL, m_settings_panel, "Noise actions");

    wxStaticBoxSizer *b_sizer = new wxStaticBoxSizer(wxHORIZONTAL, m_settings_panel, "Noise actions");
    
    wxButton *b_generate = new wxButton(m_settings_panel, ID_B_GENERATE, wxT("Generate"));
    wxButton *b_save     = new wxButton(m_settings_panel, ID_B_SAVE, wxT("Save"));
    wxButton *b_open     = new wxButton(m_settings_panel, ID_B_OPEN, wxT("Open"));

    b_sizer->Add(b_generate,  wxSizerFlags(0).Center().Border(wxALL, 1));
    b_sizer->Add(b_save, wxSizerFlags(0).Center().Border(wxALL, 1) );
    b_sizer->Add(b_open, wxSizerFlags(0).Center().Border(wxALL, 1) );

    sizer_panel->Add(b_sizer, wxSizerFlags(0).Center().Border(wxALL, 1));
    
    MainControlPamel *maini_panel = new MainControlPamel(*m_noise, m_settings_panel, wxID_ANY);
    sizer_panel->Add(maini_panel, wxSizerFlags(0).Center().Border(wxALL, 1));

    FractalSettingsPanel *fractal_panel = new FractalSettingsPanel(*m_noise, m_settings_panel, wxID_ANY);
    sizer_panel->Add(fractal_panel, wxSizerFlags(0).Center().Border(wxALL, 1));

    CelluralSettingsPanel *cellural_panel = new CelluralSettingsPanel(*m_noise, m_settings_panel, wxID_ANY);
    sizer_panel->Add(cellural_panel, wxSizerFlags(0).Center().Border(wxALL, 1));

    maini_panel->SetFractalPanel(fractal_panel);
    maini_panel->SetCelluralPanel(cellural_panel);
    
    SetSizerAndFit(sizer_panel);


    m_noise_view = new NoieseView(this, wxID_ANY, wxPoint(10, 10), wxSize(512, 512));
    m_noise->SetNoiseType(FastNoise::Value);
    m_noise_view->SetNoise(*m_noise);
    
    
    sz->Add(m_noise_view, wxSizerFlags(1).Expand().Border(wxALL, 5));
    sz->Add(m_settings_panel, wxSizerFlags(1).Expand().Border(wxALL, 5));

    SetSizerAndFit(sz);
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);

    this->SetSizeHints(wxSize(this->GetMinWidth(), this->GetMinHeight()), wxSize(this->GetMinWidth(), this->GetMinHeight()));
}
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is FastNoise front-end application",
                 "About FastNoise", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
void MainFrame::OnButtonGenerate(wxCommandEvent& event)
{
    m_noise_view->SetNoise(*m_noise);
    m_noise_view->Refresh(false);
    m_noise_view->Show();

    wxBell();
}
void MainFrame::OnButtonSave(wxCommandEvent &event)
{
    wxFileDialog SaveDialog(this, 
                            _("Choose name for your file"), 
                            wxEmptyString, 
                            wxEmptyString,
	                        ".xml",
	                        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (SaveDialog.ShowModal() == wxID_CANCEL)
        return;    

    save_to_xml(std::string(SaveDialog.GetPath().mb_str()), 
                static_cast<int>(m_noise->GetNoiseType()), 
                m_noise->GetSeed(), 
                m_noise->GetFrequency(),
                static_cast<int>(m_noise->GetInterp()),
                static_cast<int>(m_noise->GetFractalType()),
                m_noise->GetFractalOctaves(),
                m_noise->GetFractalLacunarity(),
                m_noise->GetFractalGain(),
                static_cast<int>(m_noise->GetCellularReturnType()),
                static_cast<int>(m_noise->GetCellularDistanceFunction()));
    
}

void MainFrame::OnButtonOpen(wxCommandEvent &event)
{  
   if (wxMessageBox(_("Current content has not been saved! Proceed?"), _("Please confirm"),
                     wxICON_QUESTION | wxYES_NO, this) == wxNO )
       return;
    
    wxFileDialog OpenDialog(this, 
                            _("Open XML file"), "", "",
                            "XML files (*.xml)|*.xml",
                            wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (OpenDialog.ShowModal() == wxID_CANCEL)
        return;
    

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
    
    open_from_xml(std::string(OpenDialog.GetPath().mb_str()),
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

    m_noise->SetNoiseType(static_cast<FastNoise::NoiseType>(noise_type_i));
    m_noise->SetSeed(seed_i);
    m_noise->SetFrequency(static_cast<FN_DECIMAL>(frequency_d));
    m_noise->SetInterp(static_cast<FastNoise::Interp>(interpolation_i));

    m_noise->SetFractalType(static_cast<FastNoise::FractalType>(fractal_type_i));
    m_noise->SetFractalOctaves(fractal_octave_i);
    m_noise->SetFractalLacunarity(static_cast<FN_DECIMAL>(fractal_lacunarity_d));
    m_noise->SetFractalGain(static_cast<FN_DECIMAL>(fractal_gain_d));

    m_noise->SetCellularReturnType(static_cast<FastNoise::CellularReturnType>(cellural_return_type_i));
    m_noise->SetCellularDistanceFunction(static_cast<FastNoise::CellularDistanceFunction>(cellural_distance_function_i));

}
#endif //NOISE_MAINFRAME_HH 
