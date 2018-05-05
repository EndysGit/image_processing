#ifndef FASTNOISE_NOISEVIEW_HH
#define FASTNOISE_NOISEVIEW_HH

#include "3dparty/FastNoise/include/FastNoise.h"
#include <wx-3.1/wx/panel.h>
#include <wx-3.1/wx/dcclient.h>

class NoieseView : public wxPanel
{
public:
   NoieseView(wxWindow *parent, 
              wxWindowID id, 
              const wxPoint &position, 
              const wxSize &size); 
   ~NoieseView();
    void SetNoise(const FastNoise &noise_source);
    void OnPaint(wxPaintEvent &event);
private:
   wxImage *m_image;
};

#endif // FASTNOISE_NOISEVIEW_HH 
