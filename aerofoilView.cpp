

#include <quan/gx/simple_drawing.hpp>

#include "aerofoilView.hpp"
#include <wx/log.h>

BEGIN_EVENT_TABLE(aerofoilView,wxWindow)

 EVT_PAINT(aerofoilView::OnPaint)
 EVT_SIZE(aerofoilView::OnSize)
 EVT_SCROLLWIN(aerofoilView::OnScroll)

END_EVENT_TABLE()

aerofoilView::aerofoilView(wxFrame* parent, aerofoilDoc* doc)
: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxVSCROLL | wxHSCROLL | wxALWAYS_SHOW_SB)
,m_doc(doc)
{
    this->SetScrollbar(
       wxVERTICAL  // vert or horz
      ,50          // position
      ,10         // thumb size
      ,100        // range
      , true 
     );

     this->SetScrollbar(
       wxHORIZONTAL  // vert or horz
      ,50          // position
      ,10         // thumb size
      ,100        // range
      , true 
     );
}

void aerofoilView::OnPaint(wxPaintEvent & event)
{
   wxPaintDC dc(this);
   dc.SetBackground(* wxWHITE_BRUSH); // sets background brush but doesnt clear
   dc.Clear(); //       need to invoke to clear using current background brush
   
   quan::gx::wxwidgets::graphics_context wc{
      &dc, 
      &this->m_doc->m_drawing,
      &this->m_doc->m_drawing_view,
      &this->m_device_window
   };

   this->m_doc->render(wc);
}

// update device_window size data when size changes
void aerofoilView::OnSize(wxSizeEvent & event)
{
   this->GetClientSize(
         &this->m_device_window.m_size_px.x,
         &this->m_device_window.m_size_px.y
   );
   
   // find window size in mm by getting size of pixel on display
   // may be an ondisplay change function so dont need to continaully update
   vect2_i display_size_in_px;
   wxDisplaySize(&display_size_in_px.x,&display_size_in_px.y);

   wxSize detail_display_size_mm = wxGetDisplaySizeMM();
   vect2_mm display_size_in_mm{mm{detail_display_size_mm.x},mm{detail_display_size_mm.y}};
   
   this->m_device_window.m_size_mm.x 
   = (this->m_device_window.m_size_px.x * display_size_in_mm.x) / display_size_in_px.x;
   this->m_device_window.m_size_mm.y 
   = (this->m_device_window.m_size_px.y * display_size_in_mm.y) / display_size_in_px.y;
  
  this->Refresh();
  this->Update();
}

void aerofoilView::OnScroll(wxScrollWinEvent & event)
{
  if (event.GetOrientation() == wxHORIZONTAL){
     this->OnHScroll(event);
  }else{
      this->OnVScroll(event);
  }
  this->Refresh();
  this->Update();

}

void aerofoilView::OnHScroll(wxScrollWinEvent & event)
{
   //wxLogMessage("OnHScroll called\n");
   this->m_doc->m_drawing_view.set_x_scroll_ratio( (event.GetPosition() - 50 )/100.0); 
}

void aerofoilView::OnVScroll(wxScrollWinEvent & event)
{
  // wxLogMessage("OnVScroll called\n");
   this->m_doc->m_drawing_view.set_y_scroll_ratio( -(event.GetPosition() - 50 )/100.0);
}

