#ifndef FASTNOISE_MAINFRAIM_HH
#define FASTNOISE_MAINFRAIM_HH



#include <map>
#include <array>
#include <wx-3.1/wx/wxprec.h>
#include "MainFrame.h"
#ifndef WX_PRECOMP
    #include <wx-3.1/wx/wx.h>
#endif

class NoiseApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Main entery point
wxIMPLEMENT_APP(NoiseApp);

bool NoiseApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);

   return true;
}

#endif // FASTNOISE_MAINFRAME_HH
