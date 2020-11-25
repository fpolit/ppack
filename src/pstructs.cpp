/*
 * pstruct ppack structs source file
 * pstruct implemented 24 nov 2020
 *
 *
 * Depuration:
 *
 *
 *
 * No tested functions:
 *
 *
 *
 * No implemented functions:
 *
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */


#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "../include/pstructs.hpp"
#endif // __INCLUDE_PSTRUCTS_H__


rstruct::rstruct(unsigned int min_length, unsigned int max_length)
{
  minlength = min_length;
  maxlength = max_length;
}



mstruct::mstruct(unsigned int min_length, unsigned int max_length,
                 unsigned int min_complexity, unsigned int max_complexity,
                 unsigned int min_occurence, unsigned int max_occurence,
                 vector<SCS> scharsets)
  :rstruct(min_length, max_length)
{
  mincomplexity = min_complexity;
  maxcomplexity = max_complexity;
  minoccurence = min_occurence;
  maxoccurence = max_occurence;
  charsets = scharsets;

}

pstruct::pstruct(unsigned int min_length, unsigned int max_length,
                 unsigned int min_lower, unsigned int max_lower,
                 unsigned int min_upper, unsigned int max_upper,
                 unsigned int min_digit, unsigned int max_digit,
                 unsigned int min_special, unsigned int max_special)
  :rstruct(min_length, max_length)
{
  minlower = min_lower;
  maxlower = max_lower;

  minupper = min_upper;
  maxupper = max_upper;

  mindigit = min_digit;
  maxdigit = max_digit;

  minspecial = min_special;
  maxspecial = max_special;
}
