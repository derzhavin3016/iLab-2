//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_TRIAN_HPP
#define TRIANGLES_TRIAN_HPP

#include "plane.hpp"
#include "line.hpp"

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

};

#endif //TRIANGLES_TRIAN_HPP
