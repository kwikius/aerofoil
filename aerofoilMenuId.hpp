#ifndef AEROFOILMENUID_HPP_INCLUDED
#define AEROFOILMENUID_HPP_INCLUDED

struct aerofoilMenuId{
   enum{
      Quit = 1000,
      About,
      Open,
      Save,
      SaveAs,
      Print,
      PrintPreview,
      OutputPostscript,
      ViewScale,
      DrawingSize,
      AerofoilFile,
      SectionChord,
      SectionAngle,
      SectionAxis,
      SectionTeThickness,
      SectionOffset,
      SectionFoamRectSize,
      SectionFoamRectPos
   };
};

#endif // AEROFOILMENUID_HPP_INCLUDED
