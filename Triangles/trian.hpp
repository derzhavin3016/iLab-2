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

  bool IsIntersect( const Trian &trian )
  {
    Plane p1(v1_, v2_, v3_), p2(trian.v1_, trian.v2_, trian.v3_);
    Line line_intr(Vec(0), 0);
    if (!p1.Intersect(p2, line_intr))
      return false;
    Vec V00(line_intr.Dir_ & (v1_ - line_intr.Org_)),
        V01(line_intr.Dir_ & (v2_ - line_intr.Org_)),
        V02(line_intr.Dir_ & (v3_ - line_intr.Org_));
    double t00 = V00 +


    return true;
  }
};

#endif //TRIANGLES_TRIAN_HPP
