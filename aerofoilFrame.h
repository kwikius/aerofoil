/***************************************************************
 * Name:      aerofoilFrame.h
 * Purpose:   Defines Application Frame
 * Author:    Andy (yo@yo.com)
 * Created:   2011-01-13
 * Copyright: Andy (www.yo.com)
 * License:
 **************************************************************/

#ifndef AEROFOILMAIN_H
#define AEROFOILMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <quan/gx/abc_symbol.hpp>

  struct aerofoilView;
  struct aerofoilDoc;

class aerofoilFrame: public wxFrame
{
    public:
        aerofoilFrame( aerofoilDoc* doc);
        ~aerofoilFrame();
    private:
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPrint(wxCommandEvent& event);
        void OnPrintPreview(wxCommandEvent& event);
        void OnOutputPostscript(wxCommandEvent& event);

        void OnScale(wxCommandEvent& event);
        void OnDrawingSize(wxCommandEvent& event);
        void OnSectionAerofoilFile(wxCommandEvent& event);
        void OnSectionChord(wxCommandEvent& event);
        void OnSectionAngle(wxCommandEvent& event);
        void OnSectionAxis(wxCommandEvent& event);
        void OnSectionOffset(wxCommandEvent& event);
        void OnSectionTeThickness(wxCommandEvent& event);
        void OnSectionFoamRectSize(wxCommandEvent& event);
        void OnSectionFoamRectPos(wxCommandEvent& event);
       
    private:
        void create_menus();
       
        template <typename T>
        void do_symbol_dialog(
            quan::gx::abc_symbol<T> * sym
        );
        aerofoilView* m_view;

        DECLARE_EVENT_TABLE()
};


#endif // AEROFOILMAIN_H
