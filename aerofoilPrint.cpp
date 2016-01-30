#include "aerofoilPrint.hpp"

#include "aerofoilView.hpp"
#include <quan/gx/wxwidgets/graphics_context.hpp>
#include <quan/gx/simple_device_window.hpp>
#include <quan/reciprocal_length.hpp>
#include <quan/length.hpp>

  aerofoilPrint::aerofoilPrint(aerofoilDoc* doc) : m_doc(doc){}

  bool aerofoilPrint::HasPage( int page_num)
  {
    return page_num == 1;
  }
  void aerofoilPrint::GetPageInfo(int* minpage, int* maxpage,int* pagefrom, int* pageto)
  {
     return wxPrintout::GetPageInfo(minpage,maxpage,pagefrom,pageto);
  }
   void aerofoilPrint::OnPreparePrinting()
   {
     return wxPrintout::OnPreparePrinting();
   }
   void aerofoilPrint::OnBeginPrinting()
   {
     return wxPrintout::OnBeginPrinting();
   }
   bool aerofoilPrint::OnBeginDocument(int startpage, int endpage)
   {
     return wxPrintout::OnBeginDocument(startpage,endpage);
   }
   void aerofoilPrint::OnEndDocument()
   {
     return wxPrintout::OnEndDocument();
   }
   void aerofoilPrint::OnEndPrinting()
   {
     return wxPrintout::OnEndPrinting();
   }
   bool aerofoilPrint::OnPrintPage(int page_num)
   {
      wxDC* dc = this->GetDC();
      dc->SetBackground(* wxWHITE_BRUSH); // sets background brush but doesnt clear
      dc->Clear(); //       need to invoke to clear using current background brush
     
      quan::gx::simple_device_window print_window;

      //GetPageSizePixels works fo printer  but not preview
     // GetPageSizePixels(&print_window.m_size_px.x,&print_window.m_size_px.y);
      //dc->GetSize seems to work ok for print and print preview
      dc->GetSize(&print_window.m_size_px.x,&print_window.m_size_px.y);
      quan::two_d::vect<quan::length_<int>::mm> page_size_mm;
      GetPageSizeMM(
         &page_size_mm.x.reference_numeric_value<quan::length_<int>::mm>(),
         &page_size_mm.y.reference_numeric_value<quan::length_<int>::mm>()
      );

      print_window.m_size_mm = page_size_mm;

      quan::gx::wxwidgets::graphics_context wc{
         dc, 
         &this->m_doc->m_drawing,
         &this->m_doc->m_drawing_view,
         &print_window
      };

      this->m_doc->render(wc);

      return true;
   }
