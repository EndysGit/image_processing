#ifndef FASTNOISE_NOISEVIEW_HH
#define FASTNOISE_NOISEVIEW_HH

#include "3dparty/FastNoise.h"
#include <wx/panel.h>
#include <wx/dcclient.h>

class NoieseView : public wxPanel
{
public:
   NoieseView(wxWindow *parent, 
              wxWindowID id, 
              const wxPoint &position, 
              const wxSize &size); 
   ~NoieseView()
   {
       m_image->Destroy();
   }
    void SetNoise(const FastNoise &noise_source);
    void OnPaint(wxPaintEvent &event);
private:
   wxImage *m_image;
};

NoieseView::NoieseView(wxWindow *parent, 
              wxWindowID id, 
              const wxPoint &position, 
              const wxSize &size) : 
                                     wxPanel(parent, id,  position, size, wxTRANSPARENT_WINDOW),
                                     m_image(new wxImage(size)) 
{
    this->Connect(wxEVT_PAINT, wxPaintEventHandler(NoieseView::OnPaint));
}

void 
NoieseView::SetNoise(const FastNoise  &noise_source)
{
    for (size_t x{0}; x < m_image-> GetWidth(); ++x)
        for (size_t y{0}; y < m_image->GetHeight(); ++y)
        {
            unsigned char noise = 255 * noise_source.GetNoise(x, y); 
            m_image->SetRGB(x, y, noise, noise, noise);
        }
}

void
NoieseView::OnPaint(wxPaintEvent &event)
{
    wxClientDC dc(this);
    wxBitmap bmp(*m_image);
    dc.DrawBitmap(bmp, 0, 0);
}

#endif // FASTNOISE_NOISEVIEW_HH 
