#ifndef FASTNOISE_CELLURALSETTINGS_HH
#define FASTNOISE_CELLURALSETTINGS_HH

#include "MasterHeader.h"

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
                          const wxSize &size = wxDefaultSize);
private:
    void OnChoiceReturnType(wxCommandEvent &event);
    void OnChoiceDistanceFunction(wxCommandEvent &event);
    
    wxChoice *m_ch_cell_return_type;
    wxChoice *m_ch_distance_function_type;

    FastNoise *m_noise;
    DECLARE_EVENT_TABLE()
};

#endif // FASTNOISE_CELLURALSETTINGS_HH
