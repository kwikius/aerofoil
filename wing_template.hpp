#ifndef AEROFOIL_WING_TEMPLATE_HPP_INCLUDED
#define AEROFOIL_WING_TEMPLATE_HPP_INCLUDED

#include <vector>
#include <quan/two_d/vect.hpp>
#include <quan/length.hpp>
#include <quan/angle.hpp>
//#include <quan/two_d/box.hpp>

/*
    wing shape between two sections
*/

#include "selig_aerofoil.hpp"
#include <quan/gx/symbol_value.hpp>

struct wing_template{
    
    typedef quan::length::mm mm;
    typedef quan::angle::deg deg;
    typedef quan::two_d::vect<mm> vect2_mm;
    typedef quan::two_d::vect<double> vect2_d;
    
    wing_template();
    //aerofoil chord
    quan::gx::symbol_value<mm>         m_chord;
    // geometric angle of attack , + is anticlockwise rotation
    quan::gx::symbol_value<deg>        m_angle ;
    // wedge for t.e
    quan::gx::symbol_value<mm>         m_TE_thickness;
    // selig aerofoil coords
    quan::aero::selig_aerofoil         m_aerofoil;
    // center of rotation rel aerofoil(0,0)
    quan::gx::symbol_value<vect2_mm>   m_axis;
    // rel center of drawing
    quan::gx::symbol_value<vect2_mm>   m_offset;
    // rect for foam

    void get_coords(std::vector<vect2_mm> & coords_vect) const;
    vect2_mm  calc_coord(int i) const;

};//wingtemplate


#endif // AEROFOIL_WING_TEMPLATE_HPP_INCLUDEDD
