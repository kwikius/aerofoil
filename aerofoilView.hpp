#ifndef AEROFOIL_GRAPHICS_WINDOW_HPP_INCLUDED
#define AEROFOIL_GRAPHICS_WINDOW_HPP_INCLUDED

#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <quan/two_d/vect.hpp>
#include <quan/length.hpp>
#include <quan/reciprocal_length.hpp>

#include <quan/gx/wxwidgets/graphics_context.hpp>
#include <quan/gx/simple_device_window.hpp>

#include "aerofoilDoc.hpp"

   struct aerofoilView : wxScrolledWindow{

      aerofoilView(wxFrame* parent, aerofoilDoc* doc);

      void OnPaint(wxPaintEvent & event);
      void OnSize(wxSizeEvent & event);
      void OnScroll(wxScrollWinEvent & event);
      void OnHScroll(wxScrollWinEvent & event);
      void OnVScroll(wxScrollWinEvent & event);
      
      aerofoilDoc * m_doc;

   private:

      typedef quan::two_d::vect<int>               vect2_i;
      typedef quan::two_d::vect<double>            vect2_d;
      typedef quan::length::mm                          mm;
      typedef quan::two_d::vect<mm>               vect2_mm;
      typedef quan::reciprocal_length::per_mm       per_mm;
      typedef quan::two_d::vect<per_mm>       vect2_per_mm;

      quan::gx::simple_device_window m_device_window;
          
      DECLARE_EVENT_TABLE()

   };


#endif // AEROFOIL_GRAPHICS_WINDOW_HPP_INCLUDED
