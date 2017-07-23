#include "wing_template.hpp"
#include <cassert>

/*
   aerofoil was created on heap
   wing template takes ownership of the memory
*/
wing_template::wing_template( quan::aero::aerofoil * aerofoil)
:m_aerofoil {aerofoil}
,m_chord{"Section Chord","",mm{150},mm{10},mm{100000}}
,m_angle{"Section Angle","",deg{0},deg{-90},deg{90}}
,m_TE_thickness{"TE Size","",mm{.5},mm{0},mm{100}}
,m_axis{"Aerofoil axis","X Y",vect2_mm{mm{100},mm{7.5}},
      vect2_mm{mm{-100000},mm{-100000}},
      vect2_mm{mm{100000},mm{100000}}
}
,m_offset{"Aerofoil Origin ","X Y",vect2_mm{mm{0},mm{0}},
      vect2_mm{mm{-100000},mm{-100000}},
      vect2_mm{mm{100000},mm{100000}}
}
{
  assert (m_aerofoil != nullptr);
}

wing_template::wing_template( wing_template && in)
:m_aerofoil{in.move_foil()}
 ,m_chord{in.m_chord}
 ,m_angle{in.m_angle}
 ,m_TE_thickness{in.m_TE_thickness}
 ,m_axis{in.m_axis}
 ,m_offset{in.m_offset}
{
   // assert (m_aerofoil != nullptr); This is asserted in move
}

 // current foil must be non null
 quan::aero::aerofoil* wing_template::get_foil() const
 {
    assert ( m_aerofoil != nullptr);
    return m_aerofoil;
 } 
 // transfers ownership of the pointer to the calling function
 // returns the current non null foil and sets its own pointer to null
 quan::aero::aerofoil* wing_template::move_foil()
 {
    quan::aero::aerofoil* temp = get_foil();
    m_aerofoil = nullptr;
    return temp;
 } 
 // foil has been created on heap
 // if there is a current foil
 // it is deleted
 void wing_template::set_foil(quan::aero::aerofoil* foil)
 {
   if(m_aerofoil != nullptr){
      delete m_aerofoil;
      m_aerofoil = nullptr;
   }
   m_aerofoil = foil;
 } 


wing_template::~wing_template()
{
   if ( m_aerofoil != nullptr){
      delete m_aerofoil;
   }
}

void wing_template::get_coords(std::vector<vect2_mm> & coords_vect)const
{
   assert ( m_aerofoil != nullptr);
   for ( int i = 0, numcoords = m_aerofoil->get_num_coords();
            i < numcoords; ++i){
        coords_vect.push_back(this->calc_coord(i));
   }
}

wing_template::vect2_mm  wing_template::calc_coord(int i)const
{
   assert ( m_aerofoil != nullptr);
   double te_scaling = 0.5; // add a te wedge according to te thickness

   vect2_d  coord = m_aerofoil->get_coord(i);
   if ( i > 1){
      vect2_d last = m_aerofoil->get_coord(i-1);
      if (last.x <= coord.x){
         te_scaling = -0.5;
      }
   }
   vect2_mm scaled = coord * this->m_chord.cref();
   scaled.y += coord.x * m_TE_thickness.cref() * te_scaling;
   vect2_mm tx_to_origin = scaled - this->m_axis.cref();
   vect2_mm rotated  = rotate(tx_to_origin,-this->m_angle.cref());
   vect2_mm tx_from_origin = rotated + this->m_axis.cref();
   vect2_mm result = tx_from_origin + this->m_offset.cref();
   return result;
}


