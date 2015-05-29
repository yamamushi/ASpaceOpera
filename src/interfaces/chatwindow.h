//
// Created by Jonathan Rumion on 5/29/15.
//

#ifndef ASPACEOPERA_CHATWINDOW_H
#define ASPACEOPERA_CHATWINDOW_H

#include <wx/wx.h>
#include <wx/event.h>



class chatwindow : public wxWindow
{

public:
    chatwindow(wxWindow* parent, int id);

    void OnSize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);

    void OnMouse(wxMouseEvent& event);

private:

    wxWindow* m_parent;
    wxTextCtrl *chatoutput;
    wxTextCtrl *chatinput;
    wxTextCtrl *userlist;

    int sizex, sizey;

    bool mousedragging;

    int chatinputsizex, chatinputsizey;
    int chatinputposx, chatinputposy;
    bool chatinputresize;

    int userlistsizex, userlistsizey;
    int userlistposx, userlistposy;
    bool userlistresize;






};


#endif //ASPACEOPERA_CHATWINDOW_H
