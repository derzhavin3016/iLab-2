//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_MTH_HPP
#define TRIANGLES_MTH_HPP

#define HI std::cerr <<"hi\n";

#include "trian.hpp"
#include <iostream>


template <typename T>
int sgn( T value )
{
  return (T(0) <= value) - (T(0) > value);
}


template <typename T>
T Max( T a, T b, T c )
{
  T max = 0;

  if (a > b)
    max = a;
  else
    max = b;

  if (max < c)
    max = c;

  return max;
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

int NumOfMax( double a, double b, double c )
{
  int num = 0;
  double max;

  if (a > b)
    num = 1, max = a;
  else
    num = 2, max = b;

  if (max < c)
    num = 3;

  return num;
}

int GetMidInd( int i0, int i1, int N )
{
  if (i0 < i1)
    return (i0 + i1) / 2;
  else
    return (i0 + i1 + N) / 2 % N;
}

int GetExtrInd( const Trian &trian, const Vec &point )
{
  int i0 = 0, i1 = 0;
  while (1)
  {
    int mid = GetMidInd(i0, i1, 3);
    int next = (mid + 1) % 3;
    Vec E(trian[next] - trian[mid]);
    if ((point & E) > 0)
    {
      if (mid == i0)
        return i1;
      i0 = mid;
    }
    else
    {
      int prev = (mid + 3 - 1) % 3;
      E = trian[mid] - trian[prev];
      if ((point & E) < 0)
        i1 = mid;
      else
        return mid;
    }
  }
}

bool TestIntr( const Trian &trian1, const Trian &trian2 )
{
  int i0 = 0, i1 = 2;

  for (; i0 < 3; i1 = i0, ++i0)
  {
    Vec D1((trian1[i0] - trian1[i1]).Perp2D()),
        D2((trian2[i0] - trian2[i1]).Perp2D());

    int min1 = GetExtrInd(trian2, -D1),
        min2 = GetExtrInd(trian1, -D2);
    Vec diff1(trian2[min1] - trian1[i0]),
        diff2(trian1[min2] - trian2[i0]);

    if ((D1 & diff1) > 0)
      return false;

    if ((D2 & diff2) > 0)
      return false;
  }

  return true;
}


bool Is2DIntersect( const Trian &trian1, const Vec &Norm, const Trian &trian2 )
{
  double OXY = std::abs(Norm & Vec(0, 0, 1)),
         OXZ = std::abs(Norm & Vec(0, 1, 0)),
         OYZ = std::abs(Norm & Vec(1, 0, 0));

  size_t maxind = NumOfMax(OYZ, OXZ, OXY);
  --maxind;

  Vec tr1[3];
  Vec tr2[3];

  size_t j = 0;
  for (size_t i = 0; i < 2; ++i)
  {
   if (i == maxind)
     continue;

    tr1[0][j] = trian1.v1_[i];
    tr2[0][j] = trian2.v1_[i];
    tr1[1][j] = trian1.v2_[i];
    tr2[1][j] = trian2.v2_[i];
    tr1[2][j] = trian1.v3_[i];
    tr2[2][j] = trian2.v3_[i];
    ++j;
  }
  return TestIntr(Trian(tr1[0], tr1[1], tr1[2]),
                  Trian(tr2[0], tr2[1], tr2[2]));
}

void CmpNSwap( double *dst, double *V )
{
  if (sgn(dst[1]) == sgn(dst[2]))
    std::swap(dst[2], dst[0]), std::swap(V[2], V[0]);
  else if (sgn(dst[0]) == sgn(dst[2]))
    std::swap(dst[2], dst[1]), std::swap(V[2], V[1]);
}


bool IsIntersect( const Trian &trian1, const Trian &trian2 )
{
  Plane p1(trian1.v1_, trian1.v2_, trian1.v3_),
        p2(trian2.v1_, trian2.v2_, trian2.v3_);

  if ((p1.GetNorm() % p2.GetNorm()) == Vec(0))
  {
    if (std::abs(p1.GetDist() - p2.GetDist()) < Vec::GetThreshold())
    {
      // intersect 2-d triangles
      return Is2DIntersect(trian1, p1.GetNorm(), trian2);
    }
    else
      return false;
  }
  double dist2[] = {p1.SgnDist(trian2.v1_),
                    p1.SgnDist(trian2.v2_),
                    p1.SgnDist(trian2.v3_)};

  if (sgn(dist2[0]) == sgn(dist2[1]) && sgn(dist2[1]) == sgn(dist2[2]))
    return false;

  double dist1[] = {p2.SgnDist(trian1.v1_),
                    p2.SgnDist(trian1.v2_),
                    p2.SgnDist(trian1.v3_)};

  if (sgn(dist1[0]) == sgn(dist1[1]) && sgn(dist1[1]) == sgn(dist1[2]))
    return false;

  Line intr_line(Vec(0), Vec(0));
  IsIntersect(p1, p2, intr_line, false);

  double V1[] = {intr_line.GetDir() & (trian1.v1_ - intr_line.GetOrg()),
                 intr_line.GetDir() & (trian1.v2_ - intr_line.GetOrg()),
                 intr_line.GetDir() & (trian1.v3_ - intr_line.GetOrg())};
  double V2[] = {intr_line.GetDir() & (trian2.v1_ - intr_line.GetOrg()),
                 intr_line.GetDir() & (trian2.v2_ - intr_line.GetOrg()),
                 intr_line.GetDir() & (trian2.v3_ - intr_line.GetOrg())};

  CmpNSwap(dist1, V1);
  CmpNSwap(dist2, V2);

  double t11 = V1[0] + (V1[2] - V1[0]) * dist1[0] / (dist1[0] - dist1[2]),
         t12 = V1[1] + (V1[2] - V1[1]) * dist1[1] / (dist1[1] - dist1[2]),
         t21 = V2[0] + (V2[2] - V2[0]) * dist2[0] / (dist2[0] - dist2[2]),
         t22 = V2[1] + (V2[2] - V2[1]) * dist2[1] / (dist2[1] - dist2[2]);

  if (t11 > t12)
    std::swap(t11, t12);

  if (t21 > t22)
    std::swap(t21, t22);


  if (t12 < t21 || t11 > t22)
    return false;

  return true;
}

#endif //TRIANGLES_MTH_HPP
