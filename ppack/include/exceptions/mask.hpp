/*
 * Mask exceptions
 *
 *
 * Maintainer : glozanoa <glozanoa@uni.pe>
 */

#include <exception>


#ifndef _MASK_EXCEPT_H
#define _MASK_EXCEPT_H


class InvalidMaskCharset : public std::exception
{
private:
  string charset;

public:
  InvalidMaskCharset(string mask_charset):charset{mask_charset}{};
  const char * what () const throw ()
  {
    string warning = "Invalid mask charset: " + charset;
    return warning.c_str();
  }
};



class InvalidMask : public std::exception
{
private:
  string mask;

public:
  InvalidMask(string imask):mask{imask}{}
  const char * what () const throw ()
  {
    string warning = "Invalid mask: " + mask;
    return warning.c_str();
  }
};

#endif // _MASK_EXCEPT_H
