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

  double GetDist( void )
  {
    return Dist_;
  }

  double SgnDist( const Vec &vec )
  {
    return (vec & Normal_) + Dist_;
  }

  /**
   * @brief Intersect two planes function.
   * @param[in] plane -reference to plane
   * @param [in, out] - reference to intersect line
   * @return true if planes intersect by line, false otherwise
   */
  friend bool Intersect( const Plane &plane1, const Plane &plane2, Line &line );
};

#endif //TRIANGLES_PLANE_HPP
