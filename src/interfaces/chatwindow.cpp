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
    userlistresize = false;

    SetBackgroundColour(wxString("GREY"));
    GetSize(&sizex, &sizey);

    chatinputsizex = sizex-2;
    chatinputsizey = 24;
    chatinputposx = 1;
    chatinputposy = sizey-25;
    chatinput = new wxTextCtrl(this, -1, wxT(""), wxPoint(chatinputposx, chatinputposy),
                              wxSize(chatinputsizex, chatinputsizey));

    userlistsizex = 150;
    userlistsizey = sizey-chatinputsizey-4;
    userlistposx = sizex-151;
    userlistposy = 1;
    userlist = new wxTextCtrl(this, -1, wxT(""), wxPoint(userlistposx, userlistposy),
                               wxSize(userlistsizex, userlistsizey));

    chatoutputsizex = sizex - userlistsizex - 4;
    chatoutputsizey = sizey - chatinputsizey - 4;
    chatoutputposx = 1;
    chatoutputposy = 1;
    chatoutput = new wxTextCtrl(this, -1, wxT(""), wxPoint(chatoutputposx, chatoutputposy),
                              wxSize(chatoutputsizex, chatoutputsizey));

    //userListCount = new wxStaticText(this, -1, wxT(""), wxPoint(userlistposx, 2));
    //userListCount->SetLabel(wxT("Not Connected"));


}

void chatwindow::OnSize(wxSizeEvent & event)
{
    GetSize(&sizex, &sizey);

    if(chatinputposy > sizey-25)
        chatinputposy = sizey-25;
    if(chatinputposy < 20)
        chatinputposy = 20;
    chatinput->SetPosition(wxPoint(chatinputposx, chatinputposy));

    chatinputsizex = sizex-2;
    chatinputsizey = sizey - chatinputposy - 1;
    if(chatinputsizey < 24)
        chatinputsizey = 24;

    chatinput->SetSize(chatinputsizex,chatinputsizey);


    userlistposx = sizex - userlistsizex;
    if(userlistposx > sizex-151)
        userlistposx = sizex-151;
    userlist->SetPosition(wxPoint(userlistposx, userlistposy));

    userlistsizex = sizex - userlistposx - 1;
    if(userlistsizex < 150)
        userlistsizex = 150;
    userlistsizey = sizey-chatinputsizey-4;

    userlist->SetSize(userlistsizex, userlistsizey);
    //userListCount->SetPosition(wxPoint(userlistposx, 2));

    chatoutput->SetPosition(wxPoint(chatoutputposx, chatoutputposy));

    chatoutputsizex = sizex - userlistsizex - 4;
    chatoutputsizey = sizey - chatinputsizey - 4;
    chatoutput->SetSize(chatoutputsizex, chatoutputsizey);


    Refresh();
}

void chatwindow::OnMouse(wxMouseEvent& event)
{

    const wxPoint pt = wxGetMousePosition();
    int mouseposX = pt.x - this->GetScreenPosition().x;
    int mouseposY = pt.y - this->GetScreenPosition().y;


    if((mouseposY < chatinputposy-1 && mouseposY > chatinputposy-5) || chatinputresize)
    {
        wxSetCursor(wxCURSOR_SIZENS);
        if(event.LeftDown())
        {
            chatinputresize = true;
            return;
        }
        if(event.LeftUp() && chatinputresize)
        {
            chatinputresize = false;

            GetSize(&sizex, &sizey);
            chatinputposy = mouseposY;

            if(chatinputposy > sizey-25)
                chatinputposy = sizey-25;
            if(chatinputposy < 50)
                chatinputposy = 50;
            if(chatinputposy < 20)
                chatinputposy = 20;

            chatinput->SetPosition(wxPoint(wxPoint(chatinputposx, chatinputposy)));

            chatinputsizex = sizex-2;
            chatinputsizey = sizey - chatinputposy - 1;
            if(chatinputsizey < 24)
                chatinputsizey = 24;

            chatinput->SetSize(chatinputsizex,chatinputsizey);

            if(userlistposx > sizex-151)
                userlistposx = sizex-151;
            userlist->SetPosition(wxPoint(userlistposx, userlistposy));

            if(userlistsizex < 150)
                userlistsizex = 150;
            userlistsizey = sizey-chatinputsizey-4;
            userlist->SetSize(userlistsizex, userlistsizey);

            chatoutput->SetPosition(wxPoint(chatoutputposx, chatoutputposy));

            chatoutputsizex = sizex - userlistsizex - 4;
            chatoutputsizey = sizey - chatinputsizey - 4;
            chatoutput->SetSize(chatoutputsizex, chatoutputsizey);

            Refresh();
            return;
        }
    }
    else if((mouseposX < userlistposx-1 && mouseposX > userlistposx-5) || userlistresize)
    {
        wxSetCursor(wxCURSOR_SIZEWE);
        if(event.LeftDown())
        {
            userlistresize = true;
            return;
        }
        if(event.LeftUp() && userlistresize)
        {

            userlistresize = false;

            GetSize(&sizex, &sizey);
            userlistposx = mouseposX;

            if(userlistposx > sizex-151)
                userlistposx = sizex-151;
            if(userlistposx < (sizex/3)*2)
                userlistposx = (sizex/3)*2;
            userlist->SetPosition(wxPoint(userlistposx, userlistposy));

            userlistsizex = sizex - userlistposx - 1;
            if(userlistsizex < 150)
                userlistsizex = 150;
            userlistsizey = sizey-chatinputsizey-4;
            userlist->SetSize(userlistsizex, userlistsizey);


            chatoutput->SetPosition(wxPoint(chatoutputposx, chatoutputposy));

            chatoutputsizex = sizex - userlistsizex - 4;
            chatoutputsizey = sizey - chatinputsizey - 4;
            chatoutput->SetSize(chatoutputsizex, chatoutputsizey);

            Refresh();
            return;

        }
    }
    else
    {
        wxSetCursor(wxCURSOR_DEFAULT);
        if(event.LeftDown())
        {
            chatinput->SetFocus();
            return;
        }
    }


}


void chatwindow::OnPaint(wxPaintEvent & event)
{

}