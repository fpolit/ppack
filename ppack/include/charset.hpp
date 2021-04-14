/*
 * Supported ppack characters set
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef _CHARSET_H
#define _CHARSET_H

#include <string>
using namespace std;

class charset
{
public:
  string ascii_alpha =  R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string ascii_loweralpha = R"(abcdefghijklmnopqrstuvwxyz)";
  string ascii_upperalpha = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string digits = R"(0123456789)";
  string special = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
  string all = ascii_alpha + digits + special;
  string masksymbols = R"(ludsa)";
};

typedef enum SCS {
  none,                // default value to empty SCS variable
  // basic types
  loweralpha,
  upperalpha,
  numeric,
  special,

  //common derived types (unordered)
  alpha,              // (unordered)[loweralpha + upperalpha]

  mix_alpha_special,    // (unordered)[loweralpha + upperalpha + special]
  mix_alpha_num,        // (unordered)[loweralpha + upperalpha + numeric]
  mix_special_num,      // (unordered)[special + numeric]
  mix_all,             // (unordered)[alpha, numeric, special]
}SCS;

typedef enum ACS{
  //more advance charset (ordered combinations)
  advnone,                // default value to empty AdvanceCharSet variable

  //combination of alpha(lower, upper) + special
  alpha_special,       // [(unordered)(loweralpha + upperalpha)] + special
  loweralpha_special,  // loweralpha + special
  upperalpha_special,  // upperalpha + special

  special_alpha,       // special + [(unordered)(loweralpha + upperalpha)]
  special_loweralpha,  // special + loweralpha
  special_upperalpha,  // special + upperalpha

  // combination of alpha(lower, upper) + numeric

  alpha_num,           // [(unordered)(loweralpha + upperalpha)] + numeric
  loweralpha_num,      // loweralpha + numeric
  upperalpha_num,      // upperalpha + numeric

  // combination of special + numeric

  special_num,         // special + numeric
  num_special,         // numeric + special
} ACS;


// string Values of Simple Charsets
map<SCS, string> scs_map = {
  {SCS::none, "none"},
  {SCS::loweralpha, "loweralpha"},
  {SCS::upperalpha,"upperalpha"},
  {SCS::numeric,"numeric"},
  {SCS::special,"special"},
  {SCS::alpha,"alpha"},
  {SCS::mix_alpha_special,"mix_alpha_special"},
  {SCS::mix_alpha_num, "mix_alpha_num"},
  {SCS::mix_special_num, "mix_special_num"},
  {SCS::mix_all, "mix_all"},
};


// string Values of advance Charsets
map<ACS, string> acs_map = {
  {ACS::advnone, "none"},
  {ACS::alpha_special, "alpha_special"},
  {ACS::loweralpha_special, "loweralpha_special"},
  {ACS::upperalpha_special, "upperalpha_special"},
  {ACS::special_alpha, "special_alpha"},
  {ACS::special_loweralpha, "special_loweralpha"},
  {ACS::special_upperalpha, "special_upperalpha"},
  {ACS::alpha_num, "alpha_num"},
  {ACS::loweralpha_num, "loweralpha_num"},
  {ACS::upperalpha_num, "upperalpha_num"},
  {ACS::special_num, "special_num"},
  {ACS::num_special, "num_special"},
};

#endif /*_CHARSET_H*/
