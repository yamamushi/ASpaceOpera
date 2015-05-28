//
// Created by Jonathan Rumion on 5/28/15.
//

#ifndef ASPACEOPERA_MASTERWINDOW_H
#define ASPACEOPERA_MASTERWINDOW_H

#include <wx/wx.h>
#include <wx/menu.h>

class MasterWindow : public wxFrame
{
public:
    MasterWindow(const wxString& title);

    virtual void OnAbout(wxCommandEvent& evt);
    virtual void OnPrefs(wxCommandEvent& evt);
    virtual void OnHelp(wxCommandEvent& evt);
    virtual void OnQuit(wxCommandEvent& evt);

    void OnCenterWindow(wxCommandEvent& evt);

    wxMenuBar *menubar;

    wxMenu *filemenu;
    wxMenu *windowmenu;
    wxMenu *helpmenu;

};


#endif //ASPACEOPERA_MASTERWINDOW_H
