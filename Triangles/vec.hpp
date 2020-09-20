//
// Created by andrey on 17.09.2020.
//

#ifndef TRIANGLES_VEC_HPP
#define TRIANGLES_VEC_HPP

#include <iostream>
#include <cmath>

class Vec
{
private:
  double x_, y_, z_;

public:

  /* Vector constructor method */
  Vec( double a, double b, double c ) : x_(a),
                                             y_(b),
                                             z_(c)
  {}

  /* Vector constructor method with similar coordinates */
  Vec( double a ) : x_(a),
                         y_(a),
                         z_(a)
  {}

  /* Vector copy constructor */
  Vec( const Vec&V ) : x_(V.x_),
                            y_(V.y_),
                            z_(V.z_)
  {}

  /**
   * @brief Vector add vector (reload +) function
   * @param[in] V - link to vector.
   * @return result vector;
   */
  Vec operator +( const Vec&V ) const
  {
    return Vec(x_ + V.x_, y_ + V.y_, z_ + V.z_);
  } /* End of 'operator+' function */

  /**
   * @brief Vector subtraction vector (reload -) function
   * @param - link to vector:
   * @return result vector;
   */
  Vec operator -( const Vec&V ) const
  {
    return Vec(x_ - V.x_, y_ - V.y_, z_ - V.z_);
  } /* End of 'operator-' function */

  /**
   * @brief Vector negate (reload -) function
   * @return result vector;
   */
  Vec operator -( void ) const
  {
    return Vec(-x_, -y_, -z_);
  } /* End of 'operator-' function */

  /**
   * @brief Reload assignment operator.
   * @param[in] V - link to vector
   * @return link to vector. (for multiple '=')
   */
  Vec & operator =( const Vec&V )
  {
    x_ = V.x_;
    y_ = V.y_;
    z_ = V.z_;

    return *this;
  } /* End of 'operator=' function */

  /**
   * @brief Vector add and assign vector (reload +=)
   * @param V - link to vector
   * @return link to result vector.
   */
  Vec& operator +=( const Vec&V )
  {
    x_ += V.x_;
    y_ += V.y_;
    z_ += V.z_;
    return *this;
  } /* End of 'operator+=' function */

  /**
   * @brief Get x coordinate function.
   * @return x - coordinate
   */
  double getX( void )
  {
    return x_;
  }

  /**
   * @brief Get y coordinate function.
   * @return y - coordinate
   */
  double getY( void )
  {
    return y_;
  }

  /**
   * @brief Get z coordinate function.
   * @return z - coordinate
   */
  double getZ( void )
  {
    return z_;
  }

  /**
   * @brief Vector substract and assign function (reload -=)
   * @param V - link to vector
   * @return  link to vector result.
   */
  Vec & operator -=( const Vec&V )
  {
    x_ -= V.x_;
    y_ -= V.y_;
    z_ -= V.z_;

    return *this;
  } /* End of 'operator -=' function */

  /**
   * @brief Calculate the length of a vector function
   * @return length of a vector
   */
  double operator!( void ) const
  {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
  }

  double operator &( const Vec&V ) const
  {
    return x_ * V.x_ + y_ * V.y_ + z_ * V.z_;
  }

  Vec operator %( const Vec&V ) const
  {
    return Vec(y_ * V.z_ - z_ * V.y_, z_ * V.x_ - x_ * V.z_, x_ * V.y_ - y_ * V.x_);
  }

  Vec operator *( double number ) const
  {
    return Vec(x_ * number, y_ * number, z_ * number);
  }

  Vec operator /( double number ) const
  {
    return Vec(x_ / number, y_ / number, z_ / number);
  }

  Vec & operator *=( double number )
  {
    x_ *= number;
    y_ *= number;
    z_ *= number;

    return *this;
  }

  Vec & operator /=( double number )
  {
    x_ /= number;
    y_ /= number;
    z_ /= number;

    return *this;
  }

  Vec Normalizing( void ) const
  {
    double len= !(*this);
    Vec V = *this;
    if (len == 0 || len == 1)
      return V;
    V /= len;
    return V;
  }

  Vec& Normalize( void )
  {
    double len= !(*this);
    if (len == 0 || len == 1)
      return *this;
    *this /= len;
    return *this;
  }

  double Length2( void ) const
  {
    return x_ * x_ + y_ * y_ + z_ * z_;
  }

  double Distance( const Vec&V )
  {
    return !(*this - V);
  }

  // FOR DEBUG
  friend std::ostream & operator <<( std::ostream &ost, const Vec &vec )
  {
    ost << "x = " << vec.x_ << "\n";
    ost << "y = " << vec.y_ << "\n";
    ost << "z = " << vec.z_ << "\n";

    return ost;
  }
};

#endif //TRIANGLES_VEC_HPP
