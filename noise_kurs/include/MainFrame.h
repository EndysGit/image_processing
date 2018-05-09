#ifndef FASTNOISE_MAINFRAME_HH
#define FASTNOISE_MAINFRAME_HH

#include "MainSettings.h"

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

#endif //NOISE_MAINFRAME_HH 
