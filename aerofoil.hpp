#ifndef AEROFOIL_AEROFOIL_HPP_INCLUDED
#define AEROFOIL_AEROFOIL_HPP_INCLUDED

#include <cstddef> 
#include <string>
#include <quan/two_d/vect.hpp>

namespace quan{ namespace aero{

   /*
      Abstract Base Class
      aerofoil is normalised so that le is at x= 0 and te is at x = 1.
      N.B that due to rounding errors some aerofoils may not have an exact chord of 1.
      Aerofoil consists of a number of 2d points starting at TE, going around upper 
      surface and then ending at te on lower surface
   */

   struct aerofoil{
     virtual ~aerofoil(){}
     virtual std::string get_name() const = 0;
     virtual std::size_t get_num_coords() const=0;
     virtual quan::two_d::vect<double> get_coord(int i) const=0;
     virtual quan::two_d::vect<double> get_upper_coord(double const & percent) const =0;
     virtual quan::two_d::vect<double> get_lower_coord(double const & percent) const =0;
   };

   std::ostream & operator<< (std::ostream & out,aerofoil const & aerofoil);

}} 

#endif // AEROFOIL_AEROFOIL_HPP_INCLUDED
