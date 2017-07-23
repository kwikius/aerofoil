
#include <iomanip>
#include <sstream>
#include <cmath>

#include <typeinfo>
#include <cassert>
#include <fstream>
#include <cstring>

#include <quan/two_d/out/vect.hpp>
#include <quan/from_string.hpp>

#include "selig_aerofoil.hpp"

std::size_t quan::aero::selig_aerofoil::get_num_coords() const
{
  return this->m_coords.size();
}
quan::two_d::vect<double> quan::aero::selig_aerofoil::get_coord(int i) const
{
  return this->m_coords.at(i);
}
void  quan::aero::selig_aerofoil::add_coord(quan::two_d::vect<double> const & cd)
{
  this->m_coords.push_back(cd);
}

void quan::aero::selig_aerofoil::set_name(const char* const name) 
{
  this->m_name = name;
}
std::string quan::aero::selig_aerofoil::get_name() const 
{
  return this->m_name;
}

void strip_leading(std::string & str)
{
   while (isspace(str[0])){
     str = str.substr(1,std::string::npos);
   }
}

void strip_trailing(std::string & str)
{
   for(;;){
      auto len = str.length();
      if (isspace(str[len-1])){
        str = str.substr(0,len-1);
      }else{
        break;
      }
   }
}

bool quan::aero::selig_aerofoil::load(
    std::string const & data_file,
    std::ostream & e)
{

   std::ifstream f(data_file);
   if ( ! f || f.fail()){
     e << "Invalid input file";
     return false;
   }

   std::string aerofoil_name;
   for(;;){
     if ( !f || f.eof() ){
      e << "expected aerofoil name and coords";
      return false;
     }
     getline(f,aerofoil_name);
     strip_leading(aerofoil_name);
     strip_trailing(aerofoil_name);
     if ( aerofoil_name != "") {
          break;
     }
     else continue;
   }
   std::vector<quan::two_d::vect<double> > coords;
   
   for(;;){
    if ( !f || f.eof() ) break;
     std::string line;
     getline(f,line);
     strip_leading(line);
     strip_trailing(line);
     if( line !=""){
     std::istringstream is(line);
     quan::two_d::vect<double> coord;
     
     is >> coord.x;
     // fix some selig files seem to have commas etc here
     is >> coord.y;
     coords.push_back(coord);
     }
   }
   if (coords.size() < 4){
    e << "insufficient coords in aerofoilfile";
    return false;
   }
   this->m_name = aerofoil_name;
   this->m_coords.clear();
   this->m_coords = coords;
   return true;

}

std::ostream & quan::aero::operator<< (std::ostream & out,
quan::aero::aerofoil const & aerofoil)
{
   out << aerofoil.get_name() << '\n';
   for (std::size_t i = 0; i < aerofoil.get_num_coords() ; ++i){
      quan::two_d::vect<double> cd = aerofoil.get_coord(i);
      if (std::abs(cd.x) < 0.0000005) { cd.x = 0.0;}
      if (std::abs(cd.y) < 0.0000005) { cd.y = 0.0;}
      out  
      << std::setw(12)
      << std::right
      << std::fixed
      << std::setprecision(6) 
      << cd.x ;
      out 
      << std::setw(12)
      << std::right
      << std::fixed 
      << std::setprecision(6) 
      << cd.y << '\n';
   }
   return out;
}
