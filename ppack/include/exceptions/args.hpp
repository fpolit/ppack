/*
 * args exceptions
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#include <exception>

#ifndef _ARGS_EXCEPT_H
#define _ARGS_EXCEPT_H

class Exception : public std::exception
{
private:
  string warning;

public:
  Exception(string warningMsg)
  {
    warning = warningMsg;
  }

  const char* what() const throw()
  {
    return warning.c_str();
  }
};

class InvalidSCS : public std::exception
{
private:
  string scharset;
  string warnig;

public:
  InvalidSCS(string pscs)
  {
    scharset = pscs;
    warning = "Invalid SCS type: " + scharset;
  }

  const char* what() const throw()
  {
    return warning.c_str();
  }
};

#endif // _ARGS_EXCEPT_H
