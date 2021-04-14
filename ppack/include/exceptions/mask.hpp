/*
 * Mask exceptions
 *
 *
 * Maintainer : glozanoa <glozanoa@uni.pe>
 */

#include <exception>

class InvalidMaskCharset : public std::exception
{
private:
  string mask_charset;

public:
  InvalidMaskCharset(string mask_charset);
  const char * what () const throw ();
};



class InvalidMask : public std::exception
{
private:
  string mask;

public:
  InvalidMask(string mask);
  const char * what () const throw ();
};
