//
// Created by Jonathan Rumion on 5/28/15.
//

#ifndef ASPACEOPERA_PIXELS_H
#define ASPACEOPERA_PIXELS_H


#include <wx/wx.h>

class Pixels : public wxWindow
{
public:
    Pixels(wxWindow* parent, int id);

    void OnSize(wxSizeEvent& event);
    void OnPaint(wxPaintEvent& event);

private:

    wxWindow* m_parent;


};


#endif //ASPACEOPERA_PIXELS_H
