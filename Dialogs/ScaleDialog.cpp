


#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ScaleDialog.hpp"

#include <quan/to_string.hpp>
#include <quan/from_string.hpp>
#include <quan/gx/device_window.hpp>
#include <quan/arithmetic_convert.hpp>

namespace quan{ namespace gx{

   two_d::vect<reciprocal_length::per_mm>
   get_display_px_per_mm()
   {
      two_d::vect<length_<int>::mm> size_mm;
      wxDisplaySizeMM(
         &size_mm.x.reference_numeric_value<quan::length_<int>::mm>(),
         &size_mm.y.reference_numeric_value<quan::length_<int>::mm>()
      );

      quan::two_d::vect<int> size_px;
      wxDisplaySize(&size_px.x,&size_px.y);

      return {
         static_cast<double>(size_px.x) / size_mm.x,
         static_cast<double>(size_px.y) / size_mm.y
      };
   }

   template <typename LengthType>
   wxSize to_wxSize(two_d::vect<LengthType> const & vect)
   {
      two_d::vect<reciprocal_length::per_mm> px_per_mm 
         = get_display_px_per_mm();
      return {
          arithmetic_convert<int>(px_per_mm.x * vect.x), 
          arithmetic_convert<int>(px_per_mm.y * vect.y)
      };
   }

    template <typename T>
   wxString to_wxString(T const & v)
   {
       return quan::to_string<wchar_t>(v);
   }

}} //quan::gx



namespace{
typedef quan::length::mm mm;
typedef quan::two_d::vect<mm> vmm;
//typedef quan::reciprocal_length::per_mm per_mm;
//typedef quan::two_d::vect<per_mm> vect2__per_mm;
}
using quan::gx::to_wxSize;

 scale_dialog::scale_dialog(aerofoilDoc * doc) 
 : 
 wxDialog(
     NULL,-1,wxT("Scale"),
     wxDefaultPosition,
     wxDefaultSize,
      wxDEFAULT_DIALOG_STYLE,wxT("Scale Dialog")
 ),
 m_doc(doc),
 m_scale_text{
   new wxTextCtrl{
      this,
      id_SCALE,
      quan::gx::to_wxString(m_doc->m_drawing_view.m_scale),
      wxDefaultPosition,
      wxDefaultSize
   }
 }
{
   
   auto scale_entry_hsizer = new wxBoxSizer (wxHORIZONTAL);
  
   scale_entry_hsizer->Add(
      new wxStaticText{
         this,
         -1,
         wxT("Scalerillo"),
         wxDefaultPosition,
         wxDefaultSize,
         0
      },
      wxSizerFlags{}.Border(wxALL,10).Align(wxALIGN_CENTER_VERTICAL)
   );
   scale_entry_hsizer->Add(m_scale_text,wxSizerFlags{}.Border(wxALL,10));

   auto ok_cancel = new wxBoxSizer (wxHORIZONTAL);
      ok_cancel->Add(new wxButton(this,wxID_OK),wxSizerFlags{}.Border(wxALL,10));
      ok_cancel->Add(new wxButton(this,wxID_CANCEL),wxSizerFlags{}.Border(wxALL,10));
   
   auto vsizer = new wxBoxSizer (wxVERTICAL);
      vsizer->Add(scale_entry_hsizer,0);
      vsizer->Add(ok_cancel,0);

   this->SetSizer(vsizer);
   vsizer->SetSizeHints(this);

   this->Centre();

}

 bool scale_dialog::write_changes()
{  
 // //make temp copy of database value
    auto scale = 0.0;
    wxString fail_msg;
    try{
      scale = quan::from_string<double>(std::wstring{m_scale_text->GetValue()}
      );
    }
    catch (std::exception & e){
      fail_msg += wxT("cant write Scale using \"");
      fail_msg += this->m_scale_text->GetValue();
      fail_msg += wxT("\"");
    } 
    // if all ok update database..
    if ( fail_msg.length() == 0){
      if ( m_doc->m_drawing_view.m_scale != scale){
         m_doc->m_drawing_view.m_scale = scale;
         m_doc->set_modified(true);
      }
      // etc..
      return true;
    }else{ // otherwise dont update anything
      fail_msg += wxT(", no changes written. ");
      wxMessageBox(fail_msg);
      return false;
    }
    return false;
}


