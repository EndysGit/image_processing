#ifndef NOISE_MAINFRAME_HH
#define NOISE_MAINFRAME_HH

#include <wx/frame.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/menu.h>
#include <wx/time.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include "NoiseView.h"


class MainFrame : public wxFrame
{
public:
    MainFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnButtonClick(wxCommandEvent& event);

    NoieseView *m_noise;

    DECLARE_EVENT_TABLE()
};

enum
{
    ID_Hello = 1,
    ID_BUTTON_CLICK,
    ID_NOISE_VIEW
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(ID_BUTTON_CLICK, MainFrame::OnButtonClick)
END_EVENT_TABLE();

MainFrame::MainFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World", wxDefaultPosition, wxDefaultSize) 
{
    wxButton *button1 = new wxButton(this, ID_BUTTON_CLICK, wxT("This is button1"), wxPoint(350,  10));
    wxButton *button2 = new wxButton(this, wxID_ANY, wxT("KEK"), wxPoint(350, 35));
    m_noise = new NoieseView(this, wxID_ANY, wxPoint(10, 10), wxSize(300, 300));
    FastNoise noise;
    noise.SetNoiseType(FastNoise::SimplexFractal);
    m_noise->SetNoise(noise);


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
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
void MainFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
void MainFrame::OnButtonClick(wxCommandEvent& event)
{
    FastNoise noise;
    noise.SetNoiseType(FastNoise::Simplex);
    noise.SetSeed(static_cast<int>(wxGetLocalTime()));;
    m_noise->SetNoise(noise);
    m_noise->Refresh(false);
    m_noise->Show();
    wxBell();
}
#endif //NOISE_MAINFRAME_HH 
