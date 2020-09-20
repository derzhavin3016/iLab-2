//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_MTH_HPP
#define TRIANGLES_MTH_HPP

#include "trian.hpp"

/**
   * @brief Intersect two planes function.
   * @param[in] plane -reference to plane
   * @param [in, out] - reference to intersect line
   * @return true if planes intersect by line, false otherwise
   */
bool Intersect( const Plane &plane1, const Plane &plane2, Line &line )
{
  Vec linedir(plane2.Normal_ % plane1.Normal_);
  if (linedir == Vec(0))
    return false;

  line.Dir_ = linedir;
  double s1 = plane1.Dist_, s2 = plane2.Dist_,
    n1n2dot = plane1.Normal_ & plane2.Normal_,
    n1sqr   = plane1.Normal_.Length2(),
    n2sqr   = plane2.Normal_.Length2(),
    bottom  = n1n2dot * n1n2dot - n1sqr * n2sqr,
    a = (s2 * n1n2dot - s1 * n2sqr) / bottom,
    b = (s1 * n1n2dot - s2 * n1sqr) / bottom;

  line.Org_ = plane1.Normal_ * a + plane2.Normal_ * b;
  return true;
}

bool IsIntersect( const Trian &trian1, const Trian &trian2 )
{
  Plane p1(trian1.v1_, trian1.v2_, trian1.v3_),
        p2(trian2.v1_, trian2.v2_, trian2.v3_);



  Line line_intr(Vec(0), 0);
  if (!p1.Intersect(p2, line_intr))
    return false;
  Vec V00(line_intr.Dir_ & (v1_ - line_intr.Org_)),
      V01(line_intr.Dir_ & (v2_ - line_intr.Org_)),
      V02(line_intr.Dir_ & (v3_ - line_intr.Org_));
  double t00 = V00 +


  return true;
}

#endif //TRIANGLES_MTH_HPP
