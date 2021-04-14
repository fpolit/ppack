#include <exception>
#include <string>

using namespace std;

class InvalidMaskcharset: public exception
{
private:
  string mask_charset;
public:
  InvalidMaskcharset(string invalidMaskCharset);
  const char * what() const throw ();
};


class InvalidMask: public exception
{
private:
    string mask;
public:
  InvalidMask(string invalidMask);
  const char * what() const throw ();
};


InvalidMaskcharset::InvalidMaskcharset(string invalidMaskCharset)
{
  maskCharset = invalidMaskCharset;
}

const char * InvalidMaskcharset::what() const throw ()
{
  string warningMsg = "Invalid MaskCharset: " + maskCharset;
  return warningMsg.c_str();
}


InvalidMask::InvalidMask(string invalidMask)
{
  mask = invalidMask;
}

const char * InvalidMask::what () const throw ()
{
  string warningMsg = "Invalid Mask: " + mask;
  return warningMsg.c_str();
}
