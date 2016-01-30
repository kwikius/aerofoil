

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "symbol_dialog.hpp"
#include <quan/gx/wxwidgets/to_wxString.hpp>
#include <quan/two_d/vect.hpp>
#include <quan/length.hpp>

 template <typename T>
 symbol_dialog<T>::symbol_dialog( quan::gx::abc_symbol<T>* sym)
 : wxDialog(
     NULL,-1,
     quan::gx::wxwidgets::to_wxString(sym->name()),
     wxDefaultPosition,
     wxDefaultSize,
     wxDEFAULT_DIALOG_STYLE,
     quan::gx::wxwidgets::to_wxString(sym->name())
 ) ,m_symbol_io(0)
{
    auto vsizer = new wxBoxSizer (wxVERTICAL);
   this->m_symbol_io 
   = new quan::gx::wxwidgets::dialog_symbol_io<T>(this,sym,vsizer);

   this->add_ok_cancel(vsizer);
   this->SetSizer(vsizer);
   vsizer->SetSizeHints(this);
   this->Centre();
}

template <typename T>
void symbol_dialog<T>::add_ok_cancel(wxSizer* vsizer)
{
   auto ok_cancel = new wxBoxSizer (wxHORIZONTAL);
   ok_cancel->Add(new wxButton(this,wxID_OK),wxSizerFlags{}.Border(wxALL,10));
   ok_cancel->Add(new wxButton(this,wxID_CANCEL),wxSizerFlags{}.Border(wxALL,10));
   vsizer->Add(ok_cancel,0);
}

template <typename T>
 symbol_dialog<T>::~symbol_dialog()
{
  delete m_symbol_io;
}

template <typename T>
int symbol_dialog<T>::write_changes()const
{
   return  m_symbol_io->write_changes();
}

template struct symbol_dialog<double> ;
template struct symbol_dialog<quan::length::mm> ;
template struct symbol_dialog<quan::angle::deg> ;
template struct symbol_dialog<quan::two_d::vect<quan::length::mm> > ;


