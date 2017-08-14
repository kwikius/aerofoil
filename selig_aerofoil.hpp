#ifndef SELIG_AEROFOIL_HPP_INCLUDED
#define SELIG_AEROFOIL_HPP_INCLUDED

#include "aerofoil.hpp"
#include <iostream>
#include <vector>
#include <typeinfo>

namespace quan{ namespace aero{

   /*
      An aerofoil consists of an upper surface and a lower surface which are connected at point(0,0) nominally
      The x range is from 0 to 1
      
   */

   struct selig_aerofoil : aerofoil{
     
     bool load(std::string const & filename,std::ostream & e);
        std::string get_name() const ;
        std::size_t get_num_coords() const;
        quan::two_d::vect<double> get_coord(int i) const;

        void  add_coord(quan::two_d::vect<double> const & cd);
        void set_name( const char* const name);

        quan::two_d::vect<double> get_upper_coord(double const & percent) const;
        quan::two_d::vect<double> get_lower_coord(double const & percent) const;
     private:
         std::string m_name;
         std::vector<quan::two_d::vect<double> > m_coords;
   };

}}//quan:aero

#endif // SELIG_AEROFOIL_HPP_INCLUDED
