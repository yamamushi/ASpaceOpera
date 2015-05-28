//
// Created by Jonathan Rumion on 5/28/15.
//

#include "masterwindow.h"
#include "widgetids.h"

MasterWindow::MasterWindow(const wxString& title)
        : wxFrame((wxFrame *)NULL, -1, title, wxPoint(-1,-1), wxSize(800,600),
                  wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCAPTION)
{
    auto screenX = wxSystemSettings::GetMetric( wxSYS_SCREEN_X );
    auto screenY = wxSystemSettings::GetMetric( wxSYS_SCREEN_Y );
    if(screenX < 800 || screenY < 600)
    {
        wxMessageBox(_("Error: Minimum Screen Resolution of 800x600 Required"));
        Close(true);
    }

    Centre(true);
    Maximize(true);
    SetMinSize(wxSize(800,600));
    SetMaxSize(GetSize());

    //frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxWidgets"), wxPoint(50,50), wxSize(800,600));

    menubar = new wxMenuBar();
    filemenu = new wxMenu();
    windowmenu = new wxMenu();
    helpmenu = new wxMenu();

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    wxMenuBar* menubar = new wxMenuBar();
    wxMenu* filemenu = new wxMenu();
    wxMenu* windowmenu = new wxMenu();
    wxMenu* helpmenu = new wxMenu();


    Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnAbout));
    Connect(wxID_PREFERENCES, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnPrefs));
    Connect(wxID_HELP, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnHelp));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnQuit));
    Connect(ID_CENTERMASTERWINDOW, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnCenterWindow));

    filemenu->Append(wxID_PREFERENCES, _("Preferences"));
    filemenu->Append(wxID_NEW, _("New\tCtrl-N"));
    filemenu->Append(wxID_OPEN, _("Open\tCtrl-O"));
    filemenu->Append(wxID_EXIT, _("Quit"));
    menubar->Append(filemenu, _("File"));

    windowmenu->Append(ID_CENTERMASTERWINDOW, _("Center"));
    menubar->Append(windowmenu, _("Window"));


    helpmenu->Append(wxID_HELP, _("Help"));
    helpmenu->Append(wxID_ABOUT, _("About"));
    menubar->Append(helpmenu, _("Help"));

    SetMenuBar(menubar);

    CreateStatusBar(3);
    SetStatusText(wxT("Ready"), 0);

    EnableCloseButton(false);

    Show();

}

void MasterWindow::OnAbout(wxCommandEvent& evt)
{
    wxMessageBox(_("About this application... not much to say for such a simple example, really"));
}

void MasterWindow::OnPrefs(wxCommandEvent& evt)
{
    wxMessageBox(_("Here are preferences. Not much to configure in this simple example =)"));
}

void MasterWindow::OnHelp(wxCommandEvent& evt)
{
    wxMessageBox(_("Here is a help message"));
}

void MasterWindow::OnQuit(wxCommandEvent& evt)
{
    int answer = wxMessageBox("Quit program?", "Confirm", wxYES_NO, this);
    if (answer == wxYES)
        Close();
}

void MasterWindow::OnCenterWindow(wxCommandEvent& evt)
{
    Center(true);
}
