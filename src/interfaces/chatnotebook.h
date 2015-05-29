//
// Created by Jonathan Rumion on 5/29/15.
//

#ifndef ASPACEOPERA_CHATNOTEBOOK_H
#define ASPACEOPERA_CHATNOTEBOOK_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <vector>
#include "chatwindow.h"


class chatnotebook : public wxWindow
{

public:

    chatnotebook(wxWindow* parent, int id);

    void OnSize(wxSizeEvent& event);

private:

    wxNotebook *chatwindows;

    int sizex, sizey;

    std::vector<chatwindow *> chatwindowvector;

};


#endif //ASPACEOPERA_CHATNOTEBOOK_H
