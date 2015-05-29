//
// Created by Jonathan Rumion on 5/29/15.
//

#include "chatwindow.h"
#include <stdlib.h>
#include <time.h>


chatwindow::chatwindow(wxWindow* parent, int id)
        : wxWindow(parent, id, wxDefaultPosition, wxSize(300, 250), wxNO_BORDER | wxTE_MULTILINE, "pixeltest")
{
    Connect(wxEVT_SIZE, wxSizeEventHandler(chatwindow::OnSize));
    Connect(wxEVT_MOTION, wxMouseEventHandler(chatwindow::OnMouse));
    Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(chatwindow::OnMouse));
    Connect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(chatwindow::OnMouse));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(chatwindow::OnMouse));
    Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(chatwindow::OnMouse));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(chatwindow::OnMouse));
    Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(chatwindow::OnMouse));




    mousedragging = false;
    chatinputresize = false;

    SetBackgroundColour(wxString("GREY"));
    GetSize(&sizex, &sizey);

    chatinputsizex = sizex-1;
    chatinputsizey = 24;
    chatinputposx = 1;
    chatinputposy = sizey-25;
    chatinput = new wxTextCtrl(this, -1, wxT(""), wxPoint(chatinputposx, chatinputposy),
                              wxSize(chatinputsizex, chatinputsizey));

}

void chatwindow::OnSize(wxSizeEvent & event)
{
    GetSize(&sizex, &sizey);
    chatinputposy = sizey-25;
    chatinput->SetPosition(wxPoint(wxPoint(chatinputposx, chatinputposy)));
    chatinputsizex = sizex-1;
    chatinput->SetSize(chatinputsizex,chatinputsizey);
    Refresh();
}

void chatwindow::OnMouse(wxMouseEvent& event)
{

    const wxPoint pt = wxGetMousePosition();
    int mouseposX = pt.x - this->GetScreenPosition().x;
    int mouseposY = pt.y - this->GetScreenPosition().y;


    if((mouseposY < chatinputposy && mouseposY > chatinputposy-5) || chatinputresize)
    {
        wxSetCursor(wxCURSOR_SIZENS);
        if(event.LeftDown())
        {
            chatinputresize = true;
            wxPuts("Mouse Dragging");
        }
        if(event.LeftUp() && chatinputresize)
        {
            chatinputresize = false;
            wxPuts("Mouse No Longer Dragging");
            GetSize(&sizex, &sizey);
            chatinputposy = mouseposY;
            if(chatinputposy > sizey-25)
                chatinputposy = sizey-25;
            chatinput->SetPosition(wxPoint(wxPoint(chatinputposx, chatinputposy)));
            chatinputsizex = sizex-1;
            chatinputsizey = sizey - chatinputposy - 1;
            if(chatinputsizey < 24)
                chatinputsizey = 24;
            chatinput->SetSize(chatinputsizex,chatinputsizey);
            Refresh();
        }
    }
    else
    {
        wxSetCursor(wxCURSOR_DEFAULT);
    }

}


void chatwindow::OnPaint(wxPaintEvent & event)
{

}