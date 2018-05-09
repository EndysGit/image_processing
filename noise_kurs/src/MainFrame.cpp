#include "MainFrame.h"
#include "XMLFunctions.h"

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

    this->SetSizeHints(wxSize(this->GetMinWidth(), this->GetMinHeight()), wxSize(this->GetMinWidth(), this->GetMinHeight()));
}

void
MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void
MainFrame::OnButtonGenerate(wxCommandEvent& event)
{
    m_noise_view->SetNoise(*m_noise);
    m_noise_view->Refresh(false);
    m_noise_view->Show();
}

void
MainFrame::OnButtonSave(wxCommandEvent &event)
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

void 
MainFrame::OnButtonOpen(wxCommandEvent &event)
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
