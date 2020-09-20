//
// Created by andrey on 20.09.2020.
//

#ifndef TRIANGLES_LINE_HPP
#define TRIANGLES_LINE_HPP

#include "vec.hpp"

class Line
{
private:
  Vec Org, Dir; // Origin and direction of the line

public:

  // Constructor by points
  Line( const Vec &pt1, const Vec &pt2 ) : Org(pt1),
                                           Dir((pt2 - pt1).Normalize())
  {
  }

  // Copy constructor
  Line( const Line &line ) : Org(line.Org),
                             Dir(line.Dir)
  {
  }

};

#endif //TRIANGLES_LINE_HPP
