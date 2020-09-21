//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_LINE_HPP
#define TRIANGLES_LINE_HPP

#include "vec.hpp"

class Plane;

class Line
{
private:
  Vec Org_, Dir_; // Origin and direction of the line

public:

  // Constructor by points
  Line( const Vec &pt1, const Vec &pt2 ) : Org_(pt1),
                                           Dir_((pt2 - pt1).Normalize())
  {
  }

  // Copy constructor
  Line( const Line &line ) : Org_(line.Org_),
                             Dir_(line.Dir_)
  {
  }

  const Vec & GetOrg( void ) const
  {
    return Org_;
  }

  const Vec & GetDir( void ) const
  {
    return Dir_;
  }

  friend bool IsIntersect( const Plane &plane1, const Plane &plane2, Line &line, bool IsMayPar /*= true */ );
};

// For Debug
std::ostream & operator <<( std::ostream &ost, const Line &line )
{
  ost << "Org:\n" << line.GetOrg();
  ost << "Dir:\n" << line.GetDir();

  return ost;
}

#endif //TRIANGLES_LINE_HPP
