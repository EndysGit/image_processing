#include "CelluralSettings.h"

BEGIN_EVENT_TABLE(CelluralSettingsPanel, wxPanel)
    EVT_CHOICE(ID_RETURN_TYPE, CelluralSettingsPanel::OnChoiceReturnType)
    EVT_CHOICE(ID_DISTANCE_FUNCTION, CelluralSettingsPanel::OnChoiceDistanceFunction)
END_EVENT_TABLE();

CelluralSettingsPanel::CelluralSettingsPanel(FastNoise &noise, 
                                             wxWindow *parent, 
                                             wxWindowID id, 
                                             const wxPoint &position, 
                                             const wxSize &size) 
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
