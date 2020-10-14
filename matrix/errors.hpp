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


class Error : public std::runtime_error
{
private:
  int line_;
  const char* descr_, *file_, *function_;
public:

  Error( const char* descr, int line,
         const char *file, const char* func ) : std::runtime_error(descr),
                                                descr_(descr),
                                                line_(line),
                                                file_(file),
                                                function_(func)
  {
  }

  virtual const std::string what( void )
  {
    return descr_;
  }
};

#endif //MATRIX_ERRORS_HPP
