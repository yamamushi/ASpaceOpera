//
// Created by Jonathan Rumion on 5/28/15.
//

#include "masterwindow.h"
#include "chatnotebook.h"
#include "chatwindow.h"
#include "widgetids.h"

MasterWindow::MasterWindow(const wxString& title, wxApp *parent)
        : wxFrame((wxFrame *)NULL, -1, title, wxPoint(-1,-1), wxSize(800,600),
                  wxMINIMIZE_BOX|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCAPTION), m_parent(parent)
{
    // notify wxAUI which frame to use
    m_mgr.SetManagedWindow(this);



    auto screenX = wxSystemSettings::GetMetric( wxSYS_SCREEN_X );
    auto screenY = wxSystemSettings::GetMetric( wxSYS_SCREEN_Y );
    if(screenX < 800 || screenY < 600)
    {
        wxMessageBox(_("Error: Minimum Screen Resolution of 800x600 Required"));
        Close(true);
    }

    m_connected = false;

    SetBackgroundColour(wxString("BLACK"));

    Centre(true);
    Maximize(true);
    SetMinSize(wxSize(800,600));
    SetMaxSize(GetSize());

    //frame = new wxFrame((wxFrame *)NULL, -1,  wxT("Hello wxWidgets"), wxPoint(50,50), wxSize(800,600));

    menubar = new wxMenuBar();
    filemenu = new wxMenu();
    connectionmenu = new wxMenu();
    windowmenu = new wxMenu();
    helpmenu = new wxMenu();

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
    Connect(ID_CONNECT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnConnect));
    Connect(ID_DISCONNECT, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnDisconnect));
    Connect(ID_SAVEPERSPECTIVE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnSavePerspective));
    Connect(ID_LOADPERSPECTIVE, wxEVT_COMMAND_MENU_SELECTED,
            wxCommandEventHandler(MasterWindow::OnLoadPerspective));

    filemenu->Append(wxID_PREFERENCES, _("Preferences"));
    filemenu->Append(wxID_NEW, _("New\tCtrl-N"));
    filemenu->Append(wxID_OPEN, _("Open\tCtrl-O"));
    filemenu->Append(ID_SAVEPERSPECTIVE, _("Save\tCtrl-S"), _T("Save the current window layout"));
    filemenu->Append(ID_LOADPERSPECTIVE, _("Load\tCtrl-L"), _T("Load a layout"));
    filemenu->Append(wxID_EXIT, _("Quit"));
    menubar->Append(filemenu, _("File"));

    connectionmenu->Append(ID_CONNECT, _("Connect"), _T("Connect"));
    connectionmenu->Append(ID_DISCONNECT, _("Disconnect"), _T("Disconnect from your current session"));
    menubar->Append(connectionmenu, _("Connection"));

    windowmenu->Append(ID_CENTERMASTERWINDOW, _("Center"));
    menubar->Append(windowmenu, _("Window"));


    helpmenu->Append(wxID_HELP, _("Help"));
    helpmenu->Append(wxID_ABOUT, _("About"));
    menubar->Append(helpmenu, _("Help"));

    SetMenuBar(menubar);

    CreateStatusBar(3);
    SetStatusText(wxT("Not Connected - Ready"), 0);

    EnableCloseButton(false);



    // create several text controls
    wxTextCtrl* text1 = new wxTextCtrl(this, -1, "",
                                       wxDefaultPosition, wxSize(200,150),
                                       wxNO_BORDER | wxTE_MULTILINE | wxTE_RICH2 , wxDefaultValidator, "text1");
    text1->SetBackgroundColour(wxString("Black"));
    text1->SetDefaultStyle(wxTextAttr(*wxGREEN));
    text1->AppendText("Green on black text\n");
    text1->SetDefaultStyle(wxTextAttr(wxNullColour, *wxBLACK));
    text1->AppendText("Red on black text\n");
    text1->SetDefaultStyle(wxTextAttr(*wxBLUE));
    text1->AppendText("Blue on black text\n");

    wxTextCtrl* text2 = new wxTextCtrl(this, -1, _("Sensors Online"),
                                       wxDefaultPosition, wxSize(200,150),
                                       wxNO_BORDER | wxTE_MULTILINE, wxDefaultValidator, "text2");

    wxTextCtrl* text3 = new wxTextCtrl(this, -1, _("Main content window"),
                                       wxDefaultPosition, wxSize(200,150),
                                       wxNO_BORDER | wxTE_MULTILINE, wxDefaultValidator, "text3");
    chatnotebook* chatNotebook = new chatnotebook(this, -1);

    // add the panes to the manager
    m_mgr.AddPane(text1, wxAuiPaneInfo().Name("no1").Left());
    m_mgr.AddPane(text2, wxAuiPaneInfo().Name("no2").Bottom());
    m_mgr.AddPane(chatNotebook, wxAuiPaneInfo().Name("Chat").Bottom());
    m_mgr.AddPane(text3, wxAuiPaneInfo().Name("no3").Center());

    //wxAUI hack: set minimum height to desired value, then call wxAuiPaneInfo::Fixed() to apply it
    int sizex, sizey;
    GetSize(&sizex, &sizey);
    m_mgr.GetPane(chatNotebook).MinSize(-1, sizey/3);
    m_mgr.GetPane(chatNotebook).Fixed();
    m_mgr.Update();

    //now make resizable again
    m_mgr.GetPane(chatNotebook).Resizable();

    // tell the manager to "commit" all the changes just made
    m_mgr.Update();

    wxFileName fname( m_parent->argv[0] );

    wxString ini_filename = fname.GetPath(wxPATH_GET_SEPARATOR) + "config.ini";
    wxPuts(ini_filename);
    m_config = new wxFileConfig(wxT("ASpaceOpera"), wxT("Yamamushi"), ini_filename,
                                wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
    wxConfigBase::Set(m_config);
    wxString panelPerspective;
    if ( m_config->Read("PanelPerspective", &panelPerspective) ) {
        wxPuts("Perspective Loaded");
        m_mgr.LoadPerspective(panelPerspective);
    }

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
    {
        if(m_config)
        {
            m_config->Flush();
            delete m_config;
            m_config=NULL;
        }
        wxConfigBase::Set(NULL);
        Close();
    }
}

void MasterWindow::OnSavePerspective(wxCommandEvent& evt)
{
    wxString savedperspective = m_mgr.SavePerspective();
    m_config->Write("/PanelPerspective", savedperspective);
    SetStatusText(wxT("Perspective Saved"), 0);
}

void MasterWindow::OnLoadPerspective(wxCommandEvent& evt)
{

    wxFileDialog* openFileDialog =
            new wxFileDialog(this, _(""), "", "",
                             //"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png",
                             "INI files (*.ini)|*.ini", wxFD_OPEN|wxFD_OVERWRITE_PROMPT);
                             //wxFD_SAVE|wxFD_OVERWRITE_PROMPT);


    if (openFileDialog->ShowModal() == wxID_OK){
        wxString fileName = openFileDialog->GetPath();
        wxString panelPerspective;
        wxFileName fname(fileName);
        wxString fileType = fname.GetExt();
        wxPuts(fileType);


        if(fileType == "ini") {

            auto config = new wxFileConfig(wxT("ASpaceOpera"), wxT("Yamamushi"), fileName,
                                           wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
            if (config->Read("PanelPerspective", &panelPerspective)) {
                wxPuts("Perspective Loaded");
                if (m_mgr.LoadPerspective(panelPerspective))
                    SetStatusText(wxT("Perspective Loaded"));
                else
                    SetStatusText(wxT("Error Loading File"));
            }
            else
                SetStatusText(wxT("Error Loading File"));

            delete config;
        }
    }
    //else if (openFileDialog->ShowModal() == wxID_CANCEL)
    //    return;

}

void MasterWindow::OnCenterWindow(wxCommandEvent& evt)
{
    Center(true);
}
void MasterWindow::OnConnect(wxCommandEvent& evt)
{
    SetStatusText(wxT("Connected"), 0);
}

void MasterWindow::OnDisconnect(wxCommandEvent& evt)
{
    SetStatusText(wxT("Not Connected - Ready"), 0);
}

void MasterWindow::OnOpen(wxCommandEvent& event)
{

    wxFileDialog * openFileDialog = new wxFileDialog(this);

    if (openFileDialog->ShowModal() == wxID_OK){
        wxString fileName = openFileDialog->GetPath();
//        tc->LoadFile(fileName);
    }
}