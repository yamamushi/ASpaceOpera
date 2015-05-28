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

    masterWindow = new MasterWindow(wxT("A Space Opera"));
    masterWindow->Show(true);

    //wxApp::SetExitOnFrameDelete(false);

    return true;

}

