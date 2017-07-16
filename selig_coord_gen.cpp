#include "selig_aerofoil.hpp"
#include <quan/fixed_quantity/operations/compare.hpp>
#include <quan/fixed_quantity/operations/power_root.hpp>

/*
  algorithm :
   check that input percentage is between -.0 and 1.
   if(
   find upper coordinate that is equal to the requested percentage
    within some error margin
   )
   { return the y part of that coordinate}
   else{
   find the nearest two coordinates that the coordinates lie between.
      if (one of the coordinates is the first){
        generate a before first coordinate
        send that and first three coordinates to interpolation algorithm
      }else {
        if (one of the coordinates is the last){
       generate an after last coordinate
       send the last three coordinates and that to interpolation algorithm
       }
       else get the coordiante prior to first and one after last and send to interpolation algorithm
      }

*/
namespace quan{
 namespace two_d{
   
   template <typename T>
   vect<T> interpolate(
      vect<T> const & p1,
      vect<T> const & p2,
      vect<T> const & p3,
      vect<T> const & p4,
      double const & mu
   )
   {
     auto mu2 = quan::pow<2>(mu);
     auto a0 = p4 - p3 - p1 +p2;
     auto a1 = p1 - p2 - a0;
     auto a2 = p3 - p1;
     auto a3 = p2;
     return (a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3);

   }
   
}}

quan::two_d::vect<double> 
quan::aero::selig_aerofoil::get_upper_coord(
 double const & percent
) const
{
   double cur_xpos = 2.0;
   for ( std::size_t i = 0, num_i = this->m_coords.size() ; i < num_i;++i)
   {
      if(this->m_coords[i].x > cur_xpos)
      {
         throw std::range_error("upper coordinates out of range");
      }
      cur_xpos = m_coords[i].x;
      int res = compare(cur_xpos,percent,0.000001);
      switch(res){
         case 0:
            return this->m_coords[i];
         case 1: // xpos > percent
            continue;
         case -1: //xpos > percent 
         {
            auto p2 = this->m_coords[i-1];
            auto p3 = this->m_coords[i];
            auto p4 = this->m_coords[i+1];
            //if at first iter need to generate a coord
            auto p1 = (i==1) ? p2 + (p2-p3): this->m_coords[i-2];

            double mu = (p2.x -percent)/(p2.x-p3.x);
            return interpolate(p1,p2,p3,p4,mu);
        }
        default:
         throw std::range_error("upper coordinates out of range 2");
      }
   }
    throw std::range_error("upper coordinates out of range 3");
}

quan::two_d::vect<double> 
quan::aero::selig_aerofoil::get_lower_coord(
 double const & percent
) const
{
   double cur_xpos = 2.0;
   for ( std::size_t i = this->m_coords.size()-1; i >= 0;--i)
   {
      if(this->m_coords[i].x > cur_xpos)
      {
         std::cout << "i = " << i << "\n";
         throw std::range_error("lower coordinates out of range");
      }
      cur_xpos = m_coords[i].x;
      int res = compare(cur_xpos,percent,0.000001);
      switch(res){
         case 0:
            return this->m_coords[i];
         case 1: // xpos > percent
            continue;
         case -1: //xpos > percent 
         {
            auto p2 = this->m_coords[i+1];
            auto p3 = this->m_coords[i];
            auto p4 = this->m_coords[i-1];
            //if at first iter need to generate a coord
            auto p1 = (i== this->m_coords.size()-2) ? p2 + (p2-p3): this->m_coords[i+2];

            double mu = (p2.x -percent)/(p2.x-p3.x);
            return interpolate(p1,p2,p3,p4,mu);
        }
        default:
         throw std::range_error("lower coordinates out of range 2");
      }
   }
    throw std::range_error("lower coordinates out of range 3");
}

