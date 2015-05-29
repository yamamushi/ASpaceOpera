#include <wx/wx.h>
#include "interfaces/masterwindow.h"

class ASpaceOpera: public wxApp
{
private:
    MasterWindow *masterWindow;

public:
    virtual bool OnInit();

};

IMPLEMENT_APP(ASpaceOpera)


bool ASpaceOpera::OnInit() {

    SetAppName(wxT("ASpaceOpera"));
    SetVendorName(wxT("Yamamushi"));

    masterWindow = new MasterWindow(wxT("A Space Opera"), this);
    masterWindow->Show(true);

    //wxApp::SetExitOnFrameDelete(false);

    return true;

}

