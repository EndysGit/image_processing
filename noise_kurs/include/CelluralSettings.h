#ifndef FASTNOISE_CELLURALSETTINGS_HH
#define FASTNOISE_CELLURALSETTINGS_HH

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
#include "3dparty/FastNoise/include/FastNoise.h"

enum ECelularSettings
{
    ID_DISTANCE_FUNCTION = 30,
    ID_RETURN_TYPE
};

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

#endif // FASTNOISE_CELLURALSETTINGS_HH
