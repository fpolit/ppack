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


rstruct::rstruct(unsigned int min_length, unsigned int max_length,
                 bool quietPrint,
                 string outputFile)
{
  minlength = min_length;
  maxlength = max_length;

  quiet = quietPrint;
  output = outputFile;
}


sstruct::sstruct(unsigned int min_length, unsigned int max_length,
                 bool quietPrint,
                 string outputFile,
                 vector<SCS> scharsets, // simple charsets
                 bool hide)
  :rstruct(min_length, max_length,
           quietPrint,
           outputFile)
{
  charsets = scharsets;
  hiderare = hide;
}

mstruct::mstruct(unsigned int min_length, unsigned int max_length,
                 bool quiet_print,
                 string output_file,
                 unsigned int min_complexity, unsigned int max_complexity,
                 unsigned int min_occurence, unsigned int max_occurence,
                 vector<SCS> scharsets,
                 vector<Mask> checkMasks,string checkMasksFile,
                 bool showMasks,
                 string statgen_ouput)
  :rstruct(min_length, max_length, quiet_print, output_file)
{
  // password and mas structure requirements
  mincomplexity = min_complexity;
  maxcomplexity = max_complexity;
  minoccurence = min_occurence;
  maxoccurence = max_occurence;
  charsets = scharsets;

  // check requirements
  checkmasks = checkMasks;
  checkmasksfile = checkMasksFile;

  // print requirements
  show = showMasks;

  // io parameters
  statsgenOutput = statgen_ouput; // maskgen input file

}


pstruct::pstruct(string outputFile,
                 bool quietPrint, bool showMasks,
                 unsigned int min_length, unsigned int max_length,
                 unsigned int min_lower, unsigned int max_lower,
                 unsigned int min_upper, unsigned int max_upper,
                 unsigned int min_digit, unsigned int max_digit,
                 unsigned int min_special, unsigned int max_special)
  :rstruct(min_length, max_length,
           quietPrint, outputFile)
{
  // password and mas structure requirements
  minlower = min_lower;
  maxlower = max_lower;

  minupper = min_upper;
  maxupper = max_upper;

  mindigit = min_digit;
  maxdigit = max_digit;

  minspecial = min_special;
  maxspecial = max_special;

  // print requirements
  show = showMasks;
}
