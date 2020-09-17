//
// Created by andrey on 17.09.2020.
//

#include "vec.h"

/* Vector constructor method */
Vec::Vec( double a, double b, double c ) : x_(a),
                                           y_(b),
                                           z_(c)
{}

/* Vector constructor method with similar coordinates */
Vec::Vec( double a ) : x_(a),
                       y_(a),
                       z_(a)
{}

/* Vector copy constructor */
Vec::Vec( const Vec&V ) : x_(V.x_),
                          y_(V.y_),
                          z_(V.z_)
{}

/* Vector add vector (reload +) function
* ARGUMENTS:
*   - link to vector:
*       Vec&V;
* RETURNS:
*       (Vec<double>) result vector;
*/
Vec Vec::operator +( const Vec&V ) const
{
  return Vec(x_ + V.x_, y_ + V.y_, z_ + V.z_);
} /* End of 'operator+' function */

/* Vector subtraction vector (reload -) function
* ARGUMENTS:
*   - link to vector:
*       Vec&V;
* RETURNS:
*       (Vec<double>) result vector;
*/
Vec Vec::operator -( const Vec&V ) const
{
  return Vec(x_ - V.x_, y_ - V.y_, z_ - V.z_);
} /* End of 'operator-' function */

/* Vector negative vector (reload -) function
* ARGUMENTS: NONE.
* RETURNS:
*       (Vec&) link to result vector;
*/
Vec Vec::operator -( void ) const
{
  return Vec(-x_, -y_, -z_);
} /* End of 'operator-' function */

/* Vector equal vector (reload =) function
* ARGUMENTS:
*   - link to vector:
*       Vec&V;
* RETURNS:
*       (Vec&) link to result vector;
*/
Vec & Vec::operator =( const Vec&V )
{
  x_ = V.x_;
  y_ = V.y_;
  z_ = V.z_;

  return *this;
} /* End of 'operator=' function */

/* Vector add and equal vector (reload +=) function
* ARGUMENTS:
*   - link to vector:
*       Vec&V;
* RETURNS:
*       (Vec&) link to result vector;
*/
Vec& Vec::operator +=( const Vec&V )
{
  x_ += V.x_;
  y_ += V.y_;
  z_ += V.z_;
  return *this;
} /* End of 'operator+=' function */

double Vec::getX( void )
{
  return x_;
}

double Vec::getY( void )
{
  return y_;
}

double Vec::getZ( void )
{
  return z_;
}

/* Vector substraction and equal vector (reload -=) function
* ARGUMENTS:
*   - link to vector:
*       Vec&V;
* RETURNS:
*       (Vec&) link to result vector;
*/
Vec & Vec::operator -=( const Vec&V )
{
  x_ -= V.x_;
  y_ -= V.y_;
  z_ -= V.z_;

  return *this;
} /* End of 'operator -=' function */

double Vec::operator!( void ) const
{
  return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

double Vec::operator &( const Vec&V ) const
{
  return x_ * V.x_ + y_ * V.y_ + z_ * V.z_;
}

Vec Vec::operator %( const Vec&V ) const
{
  return Vec(y_ * V.z_ - z_ * V.y_, z_ * V.x_ - x_ * V.z_, x_ * V.y_ - y_ * V.x_);
}

Vec Vec::operator *( double number ) const
{
  return Vec(x_ * number, y_ * number, z_ * number);
}

Vec Vec::operator /( double number ) const
{
  return Vec(x_ / number, y_ / number, z_ / number);
}

Vec & Vec::operator *=( double number )
{
  x_ *= number;
  y_ *= number;
  z_ *= number;

  return *this;
}

Vec & Vec::operator /=( double number )
{
  x_ /= number;
  y_ /= number;
  z_ /= number;

  return *this;
}

Vec Vec::Normalizing( void ) const
{
  double len= !(*this);
  Vec V = *this;
  if (len == 0 || len == 1)
    return V;
  V /= len;
  return V;
}

Vec& Vec::Normalize( void )
{
  double len= !(*this);
  if (len == 0 || len == 1)
    return *this;
  *this /= len;
  return *this;
}

double Vec::Length2( void ) const
{
  return x_ * x_ + y_ * y_ + z_ * z_;
}

double Vec::Distance( const Vec&V )
{
  return !(*this - V);
}