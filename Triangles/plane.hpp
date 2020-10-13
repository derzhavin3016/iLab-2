//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_PLANE_HPP
#define TRIANGLES_PLANE_HPP

#include "line.hpp"

class Plane
{
private:
  Vec Normal_;
  double Dist_;
  // Plane equation: Normal_ & V = Dist_
public:

  // constructor by normal and distance
  Plane( const Vec &Normal, double dist ) : Normal_(Normal.Normalizing()),
                                            Dist_(dist / Normal.Length())
  {
  }

  // constructor by normal & point on plane
  Plane( const Vec &Normal, const Vec &point ) : Normal_(Normal.Normalizing()),
                                                 Dist_(point & Normal_)
  {
  }

  // constructor by 3 points
  Plane( const Vec &v1, const Vec &v2, const Vec &v3 ) : Normal_(((v2 - v1) % (v3 - v1)).Normalize()),
                                                         Dist_(v1 & Normal_)
  {
  }

  double GetDist( void ) const
  {
    return Dist_;
  }

  double SgnDist( const Vec &vec ) const
  {
    return (vec & Normal_) - Dist_;
  }

  const Vec & GetNorm( void ) const
  {
    return Normal_;
  }

  /**
   * @brief Intersect two planes function.
   * @param[in] plane -reference to plane
   * @param [in, out] - reference to intersect line
   * @return true if planes intersect by line, false otherwise
   */
  friend bool IsIntersect( const Plane &plane1, const Plane &plane2, Line &line, bool IsMayPar /* = true */ );
};

std::ostream & operator << ( std::ostream &ost, const Plane &plane )
{
  ost << "Normal:\n" << plane.GetNorm() << "Dist: " << plane.GetDist() << "\n";

  return ost;
}

#endif //TRIANGLES_PLANE_HPP
