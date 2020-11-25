/*
 * pstruct ppack structs head file
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

#ifndef __PSTRUCTS_H__
#define __PSTRUCTS_H__


#ifndef __INCLUDE_STD_MAP_H_
#define __INCLUDE_STD_MAP_H_
#include<map>
#endif // __INCLUDE_STD_MAP_H_



#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif // __INCLUDE_MASK_H__



// requirement struct (maskgen and policygen requirements)
class rstruct
{
public:
  rstruct(unsigned int min_length, unsigned int max_length,
          bool quietPrint,
          string outputFile);

  // password and mas structure requirements
  unsigned int minlength;
  unsigned int maxlength;

  // print requirements
  bool quiet;

  // io parameters
  string output;
};

// statsgen requirements struct
class sstruct: public rstruct
{
public:
  sstruct(unsigned int min_length, unsigned int max_length,
          bool quietPrint,
          string outputFile,
          vector<SCS> scharsets,
          bool hide);

  // filter requierement
  vector<SCS> charsets;
  bool hiderare;
};


// maskgen requirements struct
class mstruct: public rstruct
{
public:
  mstruct(unsigned int min_length, unsigned int max_length,
          bool quiet_print,
          string output_file,
          unsigned int min_complexity, unsigned int max_complexity,
          unsigned int min_occurence, unsigned int max_occurence,
          vector<SCS> scharsets,
          vector<Mask> checkmasks,string checkmasksfile,
          bool show_masks,
          string statgen_uput);

  // password and mas structure requirements
  unsigned int mincomplexity;
  unsigned int maxcomplexity;

  unsigned int minoccurence;
  unsigned int maxoccurence;

  vector<SCS> charsets;

  // check requirements
  vector<Mask> checkmasks;
  string checkmasksfile;

  // print requirements
  bool show;

  // io parameters
  string statsgenOutput; // maskgen input file
};


// policygen requirements struct
class pstruct:public rstruct
{
public:

  pstruct(string outputFile,
          bool quietPrint, bool showMasks,
          unsigned int min_length, unsigned int max_length,
          unsigned int min_lower, unsigned int max_lower,
          unsigned int min_upper, unsigned int max_upper,
          unsigned int min_digit, unsigned int max_digit,
          unsigned int min_special, unsigned int max_special);

  // password and mas structure requirements
  unsigned int minlower;
  unsigned int maxlower;

  unsigned int minupper;
  unsigned int maxupper;

  unsigned int mindigit;
  unsigned int maxdigit;

  unsigned int minspecial;
  unsigned int maxspecial;

  // print requirements
  bool show;
};


// statgen stats struct
typedef struct statstruct
{
  map<SCS, int> scs;
  map<Mask, int> mask;
  map<unsigned int, int> length;
}statstruct;

#endif //__PSTRUCTS_H__
