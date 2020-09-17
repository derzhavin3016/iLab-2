//
// Created by andrey on 17.09.2020.
//

#ifndef TRIANGLES_VEC_H
#define TRIANGLES_VEC_H

#include <iostream>
#include <cmath>

class Vec
{
private:
  double x_, y_, z_;

public:

  Vec( double a, double b, double c );

  Vec( double a = 0 );

  Vec( const Vec&V );

  Vec operator +( const Vec&V ) const;

  Vec operator -( const Vec&V ) const;

  Vec operator -( void ) const;

  Vec& operator =( const Vec&V );

  Vec& operator +=( const Vec&V );

  double getX( void );

  double getY( void );

  double getZ( void );

  Vec& operator -=( const Vec&V );

  double operator!( void ) const;

  double operator &( const Vec&V ) const;

  Vec operator %( const Vec&V ) const;

  Vec operator *( double number ) const;

  Vec operator /( double number ) const;

  Vec & operator *=( double number );

  Vec & operator /=( double number );

  Vec Normalizing( void ) const;

  Vec& Normalize( void );

  double Length2( void ) const;

  double Distance( const Vec&V );

  //FOR DEBUG
  friend std::ostream & operator << ( std::ostream &ost, const Vec &vec )
  {
    ost << "Vec:\n" << "x = " << vec.x_;
    ost << "\ny = " << vec.y_ << "\nz = " << vec.z_ << "\n";

    return ost;
  }
};

#endif //TRIANGLES_VEC_H
