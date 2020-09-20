//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_MTH_HPP
#define TRIANGLES_MTH_HPP

#include "trian.hpp"

template <typename T>
int sgn( T value )
{
  return (T(0) < value) - (T(0) > value);
}

/**
   * @brief Intersect two planes function.
   * @param[in] plane -reference to plane
   * @param [in, out] - reference to intersect line
   * @return true if planes intersect by line, false otherwise
   */
bool IsIntersect( const Plane &plane1, const Plane &plane2, Line &line, bool IsMayPar = true )
{
  Vec linedir(plane2.Normal_ % plane1.Normal_);

  if (IsMayPar)
  {
    if (linedir == Vec(0))
      return false;
  }

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
  Plane p1(trian1.v1_, trian1.v2_, trian1.v3_);
  double dist21 = p1.SgnDist(trian2.v1_),
         dist22 = p1.SgnDist(trian2.v2_),
         dist23 = p1.SgnDist(trian2.v3_);

  if (sgn(dist21) == sgn(dist22) && sgn(dist22) == sgn(dist23))
    return false;

  Plane p2(trian2.v1_, trian2.v2_, trian2.v3_);

  if ((p1.GetNorm() % p2.GetNorm()) == Vec(0))
  {
    if (std::abs(p1.GetDist() - p2.GetDist()) < Vec::GetThreshold())
    {
      // intersect 2-d triangles
    }
    else
      return false;
  }

  double dist11 = p2.SgnDist(trian1.v1_),
         dist12 = p2.SgnDist(trian1.v2_),
         dist13 = p2.SgnDist(trian1.v3_);

  if (sgn(dist11) == sgn(dist12) && sgn(dist12) == sgn(dist13))
    return false;

  Line intr_line(Vec(0), Vec(0));
  IsIntersect(p1, p2, intr_line, false);

  double V11 = intr_line.GetDir() & (trian1.v1_ - intr_line.GetOrg()),
         V12 = intr_line.GetDir() & (trian1.v2_ - intr_line.GetOrg()),
         V13 = intr_line.GetDir() & (trian1.v3_ - intr_line.GetOrg()),
         V21 = intr_line.GetDir() & (trian2.v1_ - intr_line.GetOrg()),
         V22 = intr_line.GetDir() & (trian2.v2_ - intr_line.GetOrg()),
         V23 = intr_line.GetDir() & (trian2.v3_ - intr_line.GetOrg());

  double t11 = V11 + (V13 - V11) * dist11 / (dist11 - dist13),
         t12 = V12 + (V13 - V12) * dist12 / (dist12 - dist13),
         t21 = V21 + (V23 - V21) * dist21 / (dist21 - dist23),
         t22 = V22 + (V23 - V22) * dist22 / (dist22 - dist23);

  if ((t11 < t21 && t12 < t22) || (t11 > t21  && t12 > t22))
    return false;

  return true;
}

#endif //TRIANGLES_MTH_HPP
