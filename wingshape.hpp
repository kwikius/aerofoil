#ifndef AEROFOIL_WINGPIECE_HPP_INCLUDED
#define AEROFOIL_WINGPIECE_HPP_INCLUDED

#include <functional>
#include <quan/two_d/vect.hpp>
#include <quan/length.hpp>
#include <quan/angle.hpp>

/*
    wing shape between two sections
*/


struct wingshape{

    typedef quan::length::mm mm;
    typedef quan::two_d::vect<mm> vect2_mm;
    typedef quan::two_d::vect<double> vect2_d;
    
    mm inner_section_y_pos;
    mm outer_section_y_pos;
    /*
      function to compute the position of the spine, 
      as a function of y coordinate
    */
    std::function<vect2_mm(mm)> m_spine_function;
   /*
     function to compute the offset of the section from the spine
     as a function of y coordinate
   */
    std::function<quan::angle::rad(mm)> m_rotate_function;
   // std::function<vect2_mm(

};//wingshape


#endif // AEROFOIL_WINGPIECE_HPP_INCLUDED
