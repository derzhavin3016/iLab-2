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

  friend bool Intersect( const Plane &plane1, const Plane &plane2, Line &line );

  // For Debug
  friend std::ostream & operator <<( std::ostream &ost, const Line &line )
  {
    ost << "Org:\n" << line.Org_;
    ost << "Dir:\n" << line.Dir_;

    return ost;
  }
};

#endif //TRIANGLES_LINE_HPP
