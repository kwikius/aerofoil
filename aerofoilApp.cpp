/***************************************************************
 * Name:      aerofoilApp.cpp
 * Purpose:   Code for Application Class
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

#include "aerofoilApp.h"
#include "aerofoilFrame.h"

IMPLEMENT_APP(aerofoilApp);

bool aerofoilApp::OnInit()
{
    this->m_frame = new aerofoilFrame{new aerofoilDoc{}};
    m_frame->Show();
    return true;
}
