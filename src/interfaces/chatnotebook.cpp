//
// Created by Jonathan Rumion on 5/29/15.
//

#include "chatnotebook.h"


chatnotebook::chatnotebook(wxWindow* parent, int id)
        : wxWindow(parent, id, wxDefaultPosition, wxSize(300, 250), wxNO_BORDER | wxTE_MULTILINE, "Chat")
{

        Connect(wxEVT_SIZE, wxSizeEventHandler(chatnotebook::OnSize));


        //wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 250));

        SetBackgroundColour(wxT("Grey"));
        chatwindows = new wxNotebook(this, -1, wxPoint(-1, -1),
                                     wxSize(-1, -1), wxNB_NOPAGETHEME);


        int x = 4;
        while( x --> 0) {
                chatwindow *newWindow = new chatwindow(this, -1);
                //wxWindow* window  	 = new wxWindow(chatwindows,wxID_ANY);
                chatwindows->AddPage(newWindow, wxString::Format("%d", x));
                chatwindowvector.push_back(newWindow);
        }
        Show();

}

void chatnotebook::OnSize(wxSizeEvent& event)
{

        GetSize(&sizex, &sizey);
        chatwindows->SetSize(sizex, sizey);

        for(auto it = chatwindowvector.begin(); it != chatwindowvector.end(); ++it) {

                (*it)->OnSize(event);
        }
}
