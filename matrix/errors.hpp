//
// Created by andrey on 14.10.2020.
//

#ifndef MATRIX_ERRORS_HPP
#define MATRIX_ERRORS_HPP

#include <iostream>
#include <string>

#define LOCATION __LINE__, __FILE__, __PRETTY_FUNCTION__

#define ASSERT(cond, descr)                     \
if (!(cond))                                    \
{                                               \
  throw Error{descr, LOCATION};                 \
}


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

  virtual const std::string what( void )
  {
    return descr_;
  }
};

std::ostream & operator << ( std::ostream &ost, const Error &err )
{
  ost << "!!!!\n!! ERROR: " << err.descr_ <<
         "\n!! In file: " << err.file_ <<
         "\n!! Function: " << err.function_ <<
         "\n!! Line: " << err.line_ << "\n!!!!\n";

  return ost;
}

#endif //MATRIX_ERRORS_HPP
