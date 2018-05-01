// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#include "3dparty/FastNoise.h" 
#include "MainFrame.h"
#include "NoiseView.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
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
