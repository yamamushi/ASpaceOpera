//
// Created by Jonathan Rumion on 5/28/15.
//

#ifndef ASPACEOPERA_MASTERWINDOW_H
#define ASPACEOPERA_MASTERWINDOW_H

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/aui/aui.h>
#include <wx/stdpaths.h>
#include <wx/fileconf.h>

class MasterWindow : public wxFrame
{
public:
    MasterWindow(const wxString& title, wxApp *Parent);
    ~MasterWindow(){m_mgr.UnInit();}

    virtual void OnAbout(wxCommandEvent& evt);
    virtual void OnPrefs(wxCommandEvent& evt);
    virtual void OnHelp(wxCommandEvent& evt);
    virtual void OnQuit(wxCommandEvent& evt);

    void OnSavePerspective(wxCommandEvent& evt);
    void OnLoadPerspective(wxCommandEvent& evt);

    void OnCenterWindow(wxCommandEvent& evt);
    void OnConnect(wxCommandEvent& evt);
    void OnDisconnect(wxCommandEvent& evt);
    void OnOpen(wxCommandEvent& event);



    wxMenuBar *menubar;

    wxMenu *filemenu;
    wxMenu *connectionmenu;
    wxMenu *windowmenu;
    wxMenu *helpmenu;


private:

    wxApp *m_parent;
    wxAuiManager m_mgr;
    bool m_connected;

    wxFileConfig *m_config;

};


#endif //ASPACEOPERA_MASTERWINDOW_H
