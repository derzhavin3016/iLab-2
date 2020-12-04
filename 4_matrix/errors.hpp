//
// Created by andrey on 14.10.2020.
//

#ifndef MATRIX_ERRORS_HPP
#define MATRIX_ERRORS_HPP

#include <iostream>
#include <string>
#include <stdexcept>

#define LOCATION __LINE__, __FILE__, __PRETTY_FUNCTION__

#define ASSERT_LOC(cond, descr, LOC)                     \
if (!(cond))                                    \
{                                               \
  std::cerr << Error{descr, LOC};                 \
}

#define ASSERT(cond, descr) ASSERT_LOC(cond, descr, LOCATION)

struct Error : public std::runtime_error
{
  int line_;
  const char* descr_, *file_, *function_;


  Error( const char* descr, int line,
         const char *file, const char* func ) : std::runtime_error(descr),
                                                line_(line),
                                                descr_(descr),
                                                file_(file),
                                                function_(func)
  {
  }

  virtual const char * what( void ) const noexcept override
  {
    return descr_;
  }
};

std::ostream & operator << ( std::ostream &ost, const std::exception &ex )
{
  ost << "!!!!\n!! ERROR: " << ex.descr_ <<
         "\n!! In file: " << err.file_ <<
         "\n!! Function: " << err.function_ <<
         "\n!! Line: " << err.line_ << "\n!!!!\n";

  return ost;
}

#endif //MATRIX_ERRORS_HPP
