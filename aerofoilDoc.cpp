#include "aerofoilDoc.hpp"
#include <sstream>
#include <wx/wx.h>
#include <quan/gx/wxwidgets/to_wxString.hpp>
#include <fstream>
#include <quan/length.hpp>

aerofoilDoc::aerofoilDoc()
:
m_drawing{
   vect2_mm{mm{297},mm{210}}, // 
   vect2_mm{mm{0},mm{0}}     //origin
}, 
m_foam_rect_size{"Foam Size","X Y",vect2_mm{mm{50},mm{40}},
   vect2_mm{mm{-100000},mm{-100000}},
   vect2_mm{mm{100000},mm{100000}}
}
,m_foam_rect_pos{"Foam Pos","X Y",vect2_mm{mm{0},mm{0}},
  vect2_mm{mm{-100000},mm{-100000}},
  vect2_mm{mm{100000},mm{100000}}
},
 m_modified{true},
 m_scale_ref(0),
 m_drawing_size_ref(0)
{
   this->m_scale_ref 
   = new quan::gx::symbol_ref<double>{ 
      "Scale", "",
      this->m_drawing_view.get_scale_ref(),
      0.01, 10000.0
   };
   m_drawing_size_ref
   =  new quan::gx::symbol_ref<vect2_mm>{ 
      "Drawing size", "X  Y",
      this->m_drawing.get_size_ref(),
      vect2_mm{mm{10},mm{10}},
      vect2_mm{mm{100000},mm{1000000}}
   };
   std::ostringstream ostr;
   bool m_aerofoil_loaded = false;
   try{
     
      this->m_wing_templates.push_back(wing_template{});
      m_aerofoil_loaded = this->m_wing_templates[0].m_aerofoil.load(
         "S3021-095-84.dat", ostr
      );
   }catch (std::exception& e){
      if ( ! m_aerofoil_loaded){
         wxMessageBox(wxT("aerofoil load failed ") + quan::gx::wxwidgets::to_wxString(e.what()));
      }
   }

}

aerofoilDoc::~aerofoilDoc()
{
  delete this->m_scale_ref;
  delete this->m_drawing_size_ref;
}

void aerofoilDoc::render(quan::gx::graphics_context<aerofoilDoc::mm> const & gxc)const
{
    auto & wt = this->m_wing_templates[0];
   for (std::size_t i = 1, num = wt.m_aerofoil.get_num_coords();
         i < (num); ++i)
   {
      vect2_mm p1 = wt.calc_coord(i-1);
      vect2_mm p2 = wt.calc_coord(i);
      gxc.draw_line({p1,p2,mm{0.1}});
   }
   if ( wt.m_TE_thickness.cref() > mm{0}){
       vect2_mm p1 = wt.calc_coord(0);
       vect2_mm p2 = wt.calc_coord(wt.m_aerofoil.get_num_coords()-1 );
       gxc.draw_line({p1,p2,mm{0.1}});
   }
    vect2_mm fs = this->m_foam_rect_size.cref(); ;
    vect2_mm fpos = this->m_foam_rect_pos.cref(); ;
    vect2_mm p1 = vect2_mm{-fs.x/2,-fs.y/2} + fpos; 
    vect2_mm p2 = vect2_mm{-fs.x/2, fs.y/2} + fpos; 
    vect2_mm p3 = vect2_mm{ fs.x/2, fs.y/2} + fpos;
    vect2_mm p4 = vect2_mm{ fs.x/2,-fs.y/2} + fpos; 

    gxc.draw_line({p1,p2,mm{0.1}}); 
    gxc.draw_line({p2,p3,mm{0.1}});
    gxc.draw_line({p3,p4,mm{0.1}});
    gxc.draw_line({p4,p1,mm{0.1}});

    vect2_mm ds = this->m_drawing.get_size() ;
    vect2_mm orig = this->m_drawing.get_origin();

    p1 =  vect2_mm{-ds.x/2,-ds.y/2} - orig;
    p2 =  vect2_mm{-ds.x/2, ds.y/2} - orig;
    p3 =  vect2_mm{ ds.x/2, ds.y/2} - orig;
    p4 =  vect2_mm{ ds.x/2,-ds.y/2} - orig;

     quan::gx::abc_color::ptr gray{new quan::gx::rgb::gray{}};

    gxc.draw_line({p1,p2,mm{0.1},gray}); 
    gxc.draw_line({p2,p3,mm{0.1},gray});
    gxc.draw_line({p3,p4,mm{0.1},gray});
    gxc.draw_line({p4,p1,mm{0.1},gray});


}

void aerofoilDoc::output_postscript()const
{
   // a4 paper size = 210 mm x 297 mm
   //convert to point for postscript // point_comp
   quan::two_d::vect<mm> const paper_size{mm{210},mm{297}};

   // converts to numeric..
   quan::length::point_comp const unit{1};
   std::ofstream out("output.ps");
   //out  << "90 rotate\n";
      // translate to -210

   out << "%!PS-Adobe-3.0\n";
   out << "%%DocumentMedia: A4 595 842 0 () ()\n";
   out << "%%BeginProlog\n";
   out << "%%EndProlog\n";
   out << "%%BeginDefaults\n";
   out << "%%PageMedia: A4\n";
   out << "%%EndDefaults\n";
   out << "%%BeginSetup\n";
   out << "%%PageSize: A4\n";
   out << "%%EndSetup\n";
   out << "%%EndComments\n\n";
  
   out << "newpath\n";
// set up landscape transform...
   out << ( paper_size / (2 * unit) ).x << " " << (paper_size / (2 * unit)).y << " translate\n";
   out << "90 rotate\n"; // above code sets this up in landscape
   vect2_d  p = this->m_wing_templates[0].calc_coord(0) / unit;
   out <<  p.x << " " << p.y << " moveto\n";
   auto & wt = this->m_wing_templates[0];
   for (std::size_t i = 1, num = wt.m_aerofoil.get_num_coords();
         i < (num); ++i)
   {
       p = wt.calc_coord(i)/unit;
       out <<  p.x << " " << p.y << " lineto\n";
   }
   out << "closepath\n";
   out << "stroke\n";

    vect2_mm fs = this->m_foam_rect_size.cref(); ;
    vect2_mm fpos = this->m_foam_rect_pos.cref(); ;
    vect2_d p1 = (vect2_mm{-fs.x/2,-fs.y/2} + fpos)/unit; 
    vect2_d p2 = (vect2_mm{-fs.x/2, fs.y/2} + fpos)/unit; 
    vect2_d p3 = (vect2_mm{ fs.x/2, fs.y/2} + fpos)/unit;
    vect2_d p4 = (vect2_mm{ fs.x/2,-fs.y/2} + fpos)/unit; 
   // quan::gx::primitives::simple_line<mm> line1 = {p1,p2};
    out << "newpath\n";
   //  out << ( paper_size / (2 * unit) ).x << " " << (paper_size / (2 * unit)).y << " translate\n";
    out <<  p1.x << " " << p1.y << " moveto\n";
    out <<  p2.x << " " << p2.y << " lineto\n";
    out <<  p3.x << " " << p3.y << " lineto\n";
    out <<  p4.x << " " << p4.y << " lineto\n";
    out << "closepath\n";
   out << "stroke\n";
   out << "showpage\n";
   
}

void aerofoilDoc::set_modified(bool val)
{
   this->m_modified = val;
}

bool aerofoilDoc::is_modified() const
{
 return this->m_modified;
}