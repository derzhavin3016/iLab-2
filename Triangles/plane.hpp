//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_PLANE_HPP
#define TRIANGLES_PLANE_HPP

#include "vec.hpp"

class Plane
{
private:
  Vec Normal_;
  double Dist_;
public:

  // constructor by normal and distance
  Plane( const Vec &Normal, double dist ) : Normal_(Normal.Normalizing()),
                                            Dist_(dist)
  {
  }

  // constructor by normal & point on plane
  Plane( const Vec &Normal, const Vec &point ) : Normal_(Normal_.Normalizing()),
                                                 Dist_(point & Normal_)
  {
  }

  // constructor by 3 points
  Plane( const Vec &v1, const Vec &v2, const Vec &v3 ) : Normal_(((v2 - v1) % (v3 - v1)).Normalize()),
                                                         Dist_(v1 & Normal_)
  {
  }

};

#endif //TRIANGLES_PLANE_HPP
