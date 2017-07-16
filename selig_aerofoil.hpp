#ifndef SELIG_AEROFOIL_HPP_INCLUDED
#define SELIG_AEROFOIL_HPP_INCLUDED

//#include <quan/gc.hpp>
#include <iostream>
#include <string>
#include <quan/two_d/vect.hpp>
#include <vector>
#include <typeinfo>

namespace quan{ namespace aero{

   struct aerofoil
   {
     virtual ~aerofoil(){}
     virtual std::string get_name() const = 0;
     virtual std::size_t get_num_coords() const=0;
     virtual quan::two_d::vect<double> get_coord(int i) const=0;
     virtual quan::two_d::vect<double> get_upper_coord(double const & percent) const =0;
     virtual quan::two_d::vect<double> get_lower_coord(double const & percent) const =0;
/* 
     add get coord as percentage between 0(leading edge) and 1(trailing edge))
     virtual double get_upper_coord(double const & percent) const =0;
     virtual double get_lower_coord(double const & percent) const =0;
*/
   };

   struct selig_aerofoil : aerofoil{
     
     bool load(std::string const & filename,std::ostream & e);
        std::string  get_name() const ;
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

   std::ostream & operator<< (std::ostream & out,selig_aerofoil const & aerofoil);

}}//quan:aero

#endif // SELIG_AEROFOIL_HPP_INCLUDED
