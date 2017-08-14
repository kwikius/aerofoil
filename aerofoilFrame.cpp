/***************************************************************
 * Name:      aerofoilFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    Andy (yo@yo.com)
 * Created:   2011-01-13
 * Copyright: Andy (www.yo.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <wx/printdlg.h>
#include <wx/print.h>

#include "aerofoilFrame.h"
#include "aerofoilDoc.hpp"
#include "aerofoilView.hpp"
#include "aerofoilMenuId.hpp"
#include "aerofoilPrint.hpp"
#include <quan/to_string.hpp>
#include <quan/from_string.hpp>
#include "Dialogs/symbol_dialog.hpp"
#include <quan/gx/wxwidgets/to_wxString.hpp>
#include <fstream>

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(aerofoilFrame, wxFrame)
    EVT_CLOSE(aerofoilFrame::OnClose)
    EVT_MENU(aerofoilMenuId::Quit,                 aerofoilFrame::OnQuit)
    EVT_MENU(aerofoilMenuId::Print,                aerofoilFrame::OnPrint)
    EVT_MENU(aerofoilMenuId::PrintPreview,         aerofoilFrame::OnPrintPreview)
    EVT_MENU(aerofoilMenuId::About,                aerofoilFrame::OnAbout)
    EVT_MENU(aerofoilMenuId::ViewScale,            aerofoilFrame::OnScale)
    EVT_MENU(aerofoilMenuId::OutputPostscript,     aerofoilFrame::OnOutputPostscript)
    EVT_MENU(aerofoilMenuId::DrawingSize,          aerofoilFrame::OnDrawingSize)
    EVT_MENU(aerofoilMenuId::SectionChord,         aerofoilFrame::OnSectionChord)
    EVT_MENU(aerofoilMenuId::AerofoilFile,         aerofoilFrame::OnSectionAerofoilFile)
    EVT_MENU(aerofoilMenuId::SectionAngle,         aerofoilFrame::OnSectionAngle)
    EVT_MENU(aerofoilMenuId::SectionAxis,          aerofoilFrame::OnSectionAxis)
    EVT_MENU(aerofoilMenuId::SectionOffset,        aerofoilFrame::OnSectionOffset)
    EVT_MENU(aerofoilMenuId::SectionTeThickness,   aerofoilFrame::OnSectionTeThickness)
    EVT_MENU(aerofoilMenuId::SectionFoamRectSize,  aerofoilFrame::OnSectionFoamRectSize)
    EVT_MENU(aerofoilMenuId::SectionFoamRectPos,   aerofoilFrame::OnSectionFoamRectPos)
END_EVENT_TABLE()

aerofoilFrame::aerofoilFrame(aerofoilDoc* doc)
    : wxFrame(0L, -1, wxT("Aerofoil"))
{
    this->m_view = new aerofoilView(this,doc);
    this->create_menus();

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user!"),0);
    SetStatusText(quan::gx::wxwidgets::to_wxString(this->m_view->m_doc->m_wing_sections[0].get_foil()->get_name()),1);
  //  SetStatusText(wxbuildinfo(short_f), 1);
#endif // wxUSE_STATUSBAR

}

aerofoilFrame::~aerofoilFrame()
{
}

void aerofoilFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void aerofoilFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void aerofoilFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("aerofoil V1"));
}

void aerofoilFrame::OnScale(wxCommandEvent& event)
{
  this->do_symbol_dialog( this->m_view->m_doc->m_scale_ref);
}

void aerofoilFrame::OnDrawingSize(wxCommandEvent& event)
{
  this->do_symbol_dialog( this->m_view->m_doc->m_drawing_size_ref);
}

void aerofoilFrame::OnSectionChord(wxCommandEvent& event)
{
  this->do_symbol_dialog( &this->m_view->m_doc->m_wing_sections[0].m_chord);
}

void aerofoilFrame::OnSectionAngle(wxCommandEvent& event)
{
  this->do_symbol_dialog( &this->m_view->m_doc->m_wing_sections[0].m_angle);
}

void aerofoilFrame::OnSectionAxis(wxCommandEvent& event)
{  
   this->do_symbol_dialog( &this->m_view->m_doc->m_wing_sections[0].m_axis);
}
void aerofoilFrame::OnSectionOffset(wxCommandEvent& event)
{
   this->do_symbol_dialog( &this->m_view->m_doc->m_wing_sections[0].m_offset);
}

void aerofoilFrame::OnSectionTeThickness(wxCommandEvent& event)
{
   this->do_symbol_dialog( &this->m_view->m_doc->m_wing_sections[0].m_TE_thickness);
}

void aerofoilFrame::OnSectionFoamRectSize(wxCommandEvent& event)
{
   this->do_symbol_dialog( &this->m_view->m_doc->m_foam_rect_size);
}
void aerofoilFrame::OnSectionFoamRectPos(wxCommandEvent& event)
{
  this->do_symbol_dialog( &this->m_view->m_doc->m_foam_rect_pos);
}

void aerofoilFrame::OnSectionAerofoilFile(wxCommandEvent& event)
{
 
 auto fd = new wxFileDialog{
   this,
   wxT("Load Selig aerofoil"),  // message
   wxT(""),                     // default dir
   wxT(""),                     // default file
   wxT("*.dat"),                // wildcard
   wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR,
   wxDefaultPosition,
   wxDefaultSize,
   wxT("Selig File Dialog")
 };

   if ( (fd->ShowModal() == wxID_OK)  ){
      wxString str = fd->GetPath();
      wchar_t const * cp = str.c_str();
      std::wstring str2(cp);   
      std::string std_str = quan::to_string<char>(str2);
      std::ofstream file("output_name.txt");
      file << "#" << std_str << "#\n";

      quan::aero::selig_aerofoil* p_foil = new quan::aero::selig_aerofoil;


      if(p_foil->load(std_str,file)){
         if( this->m_view->m_doc->m_wing_sections.size() ==0){
            this->m_view->m_doc->m_wing_sections.push_back(wing_section{p_foil});
         }else{
            this->m_view->m_doc->m_wing_sections[0].set_foil(p_foil);
         }
         this->m_view->m_doc->set_modified(true);
         SetStatusText(quan::gx::wxwidgets::to_wxString(this->m_view->m_doc->m_wing_sections[0].get_foil()->get_name()),1);
      }else{
        delete p_foil;
        wxMessageBox(wxT("file load failed\n"));
      }
   }
   fd->Destroy();
   if (this->m_view->m_doc->is_modified()){
      
      this->m_view->Refresh();
      this->m_view->Update();
   }
}

void aerofoilFrame::OnOutputPostscript(wxCommandEvent& event)
{
    this->m_view->m_doc->output_postscript();
}

void aerofoilFrame::OnPrint(wxCommandEvent& event)
{
// N.B Default postscript output is pathetic..
 // hence use above fun ^..

   wxPrintData print_data;
      print_data.SetOrientation(wxLANDSCAPE);
      print_data.SetPaperId(wxPAPER_A4);
      print_data.SetColour(true);
      print_data.SetNoCopies(1);
      print_data.SetQuality(wxPRINT_QUALITY_HIGH);

   wxPrintDialogData prn_dlg_data{print_data};
      prn_dlg_data.EnablePrintToFile(true);
      prn_dlg_data.SetMinPage(1);
      prn_dlg_data.SetMaxPage(1);
      prn_dlg_data.SetFromPage(1);
      prn_dlg_data.SetToPage(1);

   if (! prn_dlg_data.IsOk()){
     wxMessageBox(wxT("printing failed"));
     return;
   }

   wxPrinter printer{&prn_dlg_data};
   aerofoilPrint printout_{this->m_view->m_doc};
   printer.Print(this,&printout_,true);
  
}

void aerofoilFrame::OnPrintPreview(wxCommandEvent& event)
{
   wxPrintData print_data;
   print_data.SetOrientation(wxLANDSCAPE);
   print_data.SetPaperId(wxPAPER_A4);
   print_data.SetColour(true);
   print_data.SetNoCopies(1);
   print_data.SetQuality(wxPRINT_QUALITY_HIGH);

   auto printout1 = new aerofoilPrint{this->m_view->m_doc};
   // print from print preview doesnt seem to work
  // auto printout2 = new aerofoilPrint{this->m_view->m_doc};
   auto preview = new wxPrintPreview{printout1,/*printout2*/ 0L,&print_data};
  // printer.Print(this,&printout_,true);
  if (preview->IsOk()){
     
     auto frame = new wxPreviewFrame{
         preview,this,wxT("Preview")
     };
     frame->Initialize();     
     frame->Show();
  }
}

void aerofoilFrame::create_menus()
{

 #if wxUSE_MENUS

    wxMenuBar* mbar = new wxMenuBar();

       wxMenu* fileMenu = new wxMenu(_T(""));
         fileMenu->Append(aerofoilMenuId::Open, _T("&Open"), _("Open File"));
         fileMenu->Append(aerofoilMenuId::Save, _T("&Save"), _("Save Current File"));
         fileMenu->Append(aerofoilMenuId::SaveAs, _T("Save &As..."), _("Save Current File with a different name"));
         fileMenu->Append(aerofoilMenuId::PrintPreview, _T("Print Preview"), _("Print preview the view"));
         fileMenu->Append(aerofoilMenuId::Print, _T("&Print..."), _("Print the view"));
         fileMenu->Append(aerofoilMenuId::OutputPostscript, _T("Postscript Output"), _("Output to Postscript file"));
         fileMenu->Append(aerofoilMenuId::Quit, _T("&Exit\tAlt-F4"), _("Exit the application"));
       mbar->Append(fileMenu, _("&File"));

       wxMenu* view_menu = new wxMenu{_T("")};
         view_menu->Append(aerofoilMenuId::ViewScale, _T("&Scale"),_("Scale the view of the drawing"));
       mbar->Append(view_menu,wxT("&View"));
       wxMenu* drawing_menu = new wxMenu{_T("")};
         wxMenu* section_menu = new wxMenu{_T("")};
           section_menu->Append(aerofoilMenuId::AerofoilFile, _T("&Aerofoil"),_("Change the section  aerofoil"));
           section_menu->Append(aerofoilMenuId::SectionChord, _T("&Chord"),_("Change the section  chord"));
           section_menu->Append(aerofoilMenuId::SectionAngle, _T("&Incidence Angle"),_("Change the section incidence angle"));
           section_menu->Append(aerofoilMenuId::SectionAxis, _T("&Rotation Axis"),_("Change the section rotation axis"));
           section_menu->Append(aerofoilMenuId::SectionOffset, _T("&Origin"),_("Change the section origin"));
           section_menu->Append(aerofoilMenuId::SectionTeThickness, _T("&Trailing edge Thickness"),_("Change the section trailing edge thickness"));
           section_menu->Append(aerofoilMenuId::SectionFoamRectSize, _T("Foam &Size"),
            _("Change the size of the Foam rectangle"));
           section_menu->Append(aerofoilMenuId::SectionFoamRectPos, _T("Foam &Pos"),
            _("Change the position of the foam rectangle"));
         drawing_menu->AppendSubMenu(section_menu,wxT("&Section"));
         drawing_menu->Append(aerofoilMenuId::DrawingSize, _T("&Resize"),_("Resize the drawing"));
       mbar->Append(drawing_menu,wxT("&Drawing"));

       wxMenu* helpMenu = new wxMenu(_T(""));
         helpMenu->Append(aerofoilMenuId::About, _("&About\tF1"), _("Show info about this application"));
       mbar->Append(helpMenu, _("&Help"));
    this->SetMenuBar(mbar);
#endif // wxUSE_MENUS

}

template <typename T>
void aerofoilFrame::do_symbol_dialog(
   quan::gx::abc_symbol<T> * sym
)
{
   auto d = new symbol_dialog<T>{sym};
   if ( (d->ShowModal() == wxID_OK) && (d->write_changes() == 1) ){
      this->m_view->m_doc->set_modified(true);
   }
   d->Destroy();
   if (this->m_view->m_doc->is_modified()){
      this->m_view->Refresh();
      this->m_view->Update();
   }
}

//template void aerofoilFrame::do_symbol_dialog<double>(
//   quan::gx::abc_symbol<double> *
//);
