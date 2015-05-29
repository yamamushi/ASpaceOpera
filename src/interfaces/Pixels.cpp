//
// Created by Jonathan Rumion on 5/28/15.
//

#include "Pixels.h"
#include <stdlib.h>
#include <time.h>


Pixels::Pixels(wxWindow* parent, int id)
       : wxWindow(parent, id, wxDefaultPosition, wxSize(200, 150), wxNO_BORDER | wxTE_MULTILINE, "pixeltest")
{

    m_parent = parent;

    Connect(wxEVT_PAINT, wxPaintEventHandler(Pixels::OnPaint));
    Connect(wxEVT_SIZE, wxSizeEventHandler(Pixels::OnSize));

    wxPaintDC dc(this);

    wxCoord xpos, ypos;
    GetPosition(&xpos, &ypos);

    wxSize size = this->GetSize();

    for (int i = 0; i<1000; i++)
    {
        auto x = rand() % size.x + 1;
        auto y = rand() % size.y + 1;
        dc.DrawPoint(x-xpos, y-ypos);
    }

}

void Pixels::OnSize(wxSizeEvent & event)
{
    Refresh();
}

void Pixels::OnPaint(wxPaintEvent & event)
{
    wxPaintDC dc(this);

    wxCoord xpos, ypos;
    GetPosition(&xpos, &ypos);

    wxSize size = this->GetSize();

    for (int i = 0; i<1000; i++)
    {
        auto x = rand() % size.x + 1;
        auto y = rand() % size.y + 1;
        dc.DrawPoint(x-xpos, y-ypos);
    }
}