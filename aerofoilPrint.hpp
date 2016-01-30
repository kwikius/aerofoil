#ifndef PRINTOUT_HPP_INCLUDED
#define PRINTOUT_HPP_INCLUDED

#include <wx/wx.h>
#include <wx/print.h>

#include <quan/two_d/vect.hpp>
#include <quan/length.hpp>
#include <quan/reciprocal_length.hpp>

#include "aerofoilDoc.hpp"

struct aerofoilPrint : wxPrintout{
   aerofoilPrint(aerofoilDoc * doc);
   bool HasPage( int page_num);
   void GetPageInfo(int* minpage, int* maxpage,int* pagefrom, int* pageto);
   void OnPreparePrinting();
   void OnBeginPrinting();
   bool OnBeginDocument(int startpage, int endpage);
   void OnEndDocument();
   void OnEndPrinting();
   bool OnPrintPage(int page_num);

   private:
   aerofoilDoc * m_doc;

};


#endif // PRINTOUT_HPP_INCLUDED
