#ifndef AEROFOILDOC_HPP_INCLUDED
#define AEROFOILDOC_HPP_INCLUDED

#include <quan/gx/simple_drawing.hpp>
#include <quan/gx/simple_drawing_view.hpp>
#include <quan/gx/graphics_context.hpp>
#include <quan/length.hpp>
#include <quan/two_d/vect.hpp>
#include <quan/gx/symbol_ref.hpp>
#include "selig_aerofoil.hpp"
#include <vector>

#include "wing_template.hpp"

struct aerofoilDoc{

    aerofoilDoc();
    bool is_modified() const;
    void set_modified(bool val);

    typedef quan::length::mm mm;
    typedef quan::two_d::vect<mm> vect2_mm;
    typedef quan::two_d::vect<double> vect2_d;

    std::vector<wing_template> m_wing_templates;

    quan::gx::simple_drawing<mm> m_drawing ;
    quan::gx::simple_drawing_view m_drawing_view;

    quan::gx::symbol_value<vect2_mm>   m_foam_rect_size;
    quan::gx::symbol_value<vect2_mm>   m_foam_rect_pos;

    void render(quan::gx::graphics_context<mm> const & gxc) const;
    void output_postscript() const;
 private:
    bool m_modified;
  //  bool m_aerofoil_loaded;
 public:
   typedef quan::gx::symbol_ref<double> sym_ref_d;
   typedef quan::gx::symbol_ref<mm> sym_ref_mm;
   typedef quan::gx::symbol_ref<quan::angle::deg> sym_ref_deg;
   typedef quan::gx::symbol_ref<vect2_mm> sym_ref_vect2_mm;
   
   sym_ref_d* m_scale_ref;
   sym_ref_vect2_mm* m_drawing_size_ref;
   ~aerofoilDoc();

};

#endif // AEROFOILDOC_HPP_INCLUDED
