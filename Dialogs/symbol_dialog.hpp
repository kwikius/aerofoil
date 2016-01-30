#ifndef SCALAR_DIALOG_HPP_INCLUDED
#define SCALAR_DIALOG_HPP_INCLUDED

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <wx/wx.h>

#include <quan/gx/abc_symbol.hpp>
#include <quan/gx/wxwidgets/dlg_symbol_io.hpp>

    template <typename T>
    struct symbol_dialog : wxDialog {
     symbol_dialog(quan::gx::abc_symbol<T>* sym);
     ~symbol_dialog();
     /*
  returns  
  1 if changed,
  0 if ok but not changed,
  or -1 if failed due usually incorrect text input
*/
    int write_changes() const;
    protected:
      void add_ok_cancel(wxSizer* vsizer);
    private:
        quan::gx::wxwidgets::dialog_symbol_io<T>* m_symbol_io;
};


#endif // SCALARDIALOG_HPP_INCLUDED
