#ifndef SCALEDIALOG_HPP_INCLUDED
#define SCALEDIALOG_HPP_INCLUDED

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include <wx/wx.h>
#include "../aerofoilDoc.hpp"

    struct scale_dialog : wxDialog {
       enum { id_SCALE = 1000};
    scale_dialog( aerofoilDoc * doc ) ;

    bool write_changes();

    private:
      aerofoilDoc* m_doc;
      wxTextCtrl * m_scale_text;
};


#endif // SCALEDIALOG_HPP_INCLUDED
