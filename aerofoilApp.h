/***************************************************************
 * Name:      aerofoilApp.h
 * Purpose:   Defines Application Class
 * Author:    Andy (yo@yo.com)
 * Created:   2011-01-13
 * Copyright: Andy (www.yo.com)
 * License:
 **************************************************************/

#ifndef AEROFOILAPP_H
#define AEROFOILAPP_H

#include <wx/app.h>
#include "aerofoilView.hpp"
#include "aerofoilDoc.hpp"

class aerofoilApp : public wxApp
{
    public:
        virtual bool OnInit();
   private:
     wxFrame * m_frame;

};

#endif // AEROFOILAPP_H
