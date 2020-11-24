/*
 * charset namespace definition
 * character head file reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef __CHARACTER_H__
#define __CHARACTER_H__


#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

using namespace std;

namespace charset
{
  string ascci_letters =  R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string ascii_lowercase = R"(abcdefghijklmnopqrstuvwxyz)";
  string ascii_uppercase = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string digits = R"(0123456789)";
  string special = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
  string printable = R"(0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c)";
  string whitespace = R"( \t\n\r\x0b\x0c)";
  string masksymbols = R"(ludsa)";


  bool isdigit(string letther)
  {
    if (digits.find(letther) == string::npos)
      {
        return false;
      }
    return true;
  }

  bool islower(string letther)
  {
    if (ascii_lowercase.find(letther) == string::npos)
      {
        return false;
      }
    return true;
  }

  bool isupper(string letther)
  {
    if (ascii_uppercase.find(letther) == string::npos)
      {
        return false;
      }
    return true;
  }

  bool isspecial(string letther)
  {
    if (special.find(letther) == string::npos)
      {
        return false;
      }
    return true;
  }
}

#endif // __CHARACTER_H__
