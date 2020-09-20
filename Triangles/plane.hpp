//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_PLANE_HPP
#define TRIANGLES_PLANE_HPP

#include "vec.hpp"
#include "line.hpp"

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

  /**
   * @brief Intersect two planes function.
   * @param[in] plane -reference to plane
   * @param [in, out] - reference to intersect line
   * @return true if planes intersect by line, false otherwise
   */
  bool Intersect( const Plane &plane, Line &line )
  {
    Vec linedir(plane.Normal_ % Normal_);
    if (linedir.Length2() == 0)
      return false;

    line.Dir_ = linedir;
    double s1 = Dist_, s2 = plane.Dist_,
           n1n2dot = Normal_ & plane.Normal_,
           n1sqr   = Normal_.Length2(),
           n2sqr   = plane.Normal_.Length2(),
           bottom  = n1n2dot * n1n2dot - n1sqr * n2sqr,
           a = (s2 * n1n2dot - s1 * n2sqr) / bottom,
           b = (s1 * n1n2dot - s2 * n1sqr) / bottom;

    line.Org_ = Normal_ * a + plane.Normal_ * b;
    return true;
  }

};

#endif //TRIANGLES_PLANE_HPP
