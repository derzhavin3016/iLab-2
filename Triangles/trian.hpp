//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_TRIAN_HPP
#define TRIANGLES_TRIAN_HPP

#include "plane.hpp"

class Trian
{
private:
  Vec v1_, v2_, v3_;
public:

  // constructor by 3 points
  Trian( const Vec &v1, const Vec &v2, const Vec &v3 ) : v1_(v1),
                                                         v2_(v2),
                                                         v3_(v3)
  {
  }

  Trian( const Trian &trian ) : v1_(trian.v1_),
                                v2_(trian.v2_),
                                v3_(trian.v3_)
  {
  }

  friend bool Is2DIntersect( const Trian &trian1, const Vec &Norm, const Trian &trian2 );

  friend bool IsIntersect( const Trian &trian1, const Trian &trian2 );
};

#endif //TRIANGLES_TRIAN_HPP
