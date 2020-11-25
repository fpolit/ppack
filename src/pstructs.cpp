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



#ifndef __INCLUDE_STD_EXCEPTION_H__
#define __INCLUDE_STD_EXCEPTION_H__
#include <exception>
#endif //__INCLUDE_STD_EXCEPTION_H__

// void validate_arguments(po::variables_map vm, pstruct *pargs)

// }


rstruct::rstruct(unsigned int min_length, int max_length,
                 bool quietPrint,
                 string outputFile)
{
  minlength = min_length;
  maxlength = max_length;

  quiet = quietPrint;
  output = outputFile;
}


sstruct::sstruct(unsigned int min_length, int max_length,
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

mstruct::mstruct(unsigned int min_length, int max_length,
                 bool quiet_print,
                 string output_file,
                 unsigned int min_complexity, int max_complexity,
                 unsigned int min_occurence, int max_occurence,
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
                 unsigned int min_length, int max_length,
                 unsigned int min_lower, int max_lower,
                 unsigned int min_upper, int max_upper,
                 unsigned int min_digit, int max_digit,
                 unsigned int min_special, int max_special)
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

pstruct::pstruct(po::variables_map vm)
/*
 * init a pstruct with all the paramenters entered to vm (from cli using flags)
 */
{
  //Output File parameter(files section)
  if(vm.count("output"))
    {
      output = vm["output"].as<string>();
    }

  //print parameters(print section)
  if(vm.count("quiet"))
    {
      quiet = vm["quiet"].as<bool>();
    }

  if(vm.count("show"))
    {
      show = vm["show"].as<bool>();
    }

  //length parameters (mask section)
  if(vm.count("minlength") && vm.count("maxlength"))
    {
      minlength = vm["minlength"].as<int>();
      maxlength = vm["maxlength"].as<int>();
      if((int)minlength > maxlength)
        throw "Ivalid paramemters";
    }
  else if(vm.count("minlength"))
    {
      minlength = vm["minlength"].as<int>();
      // Because we do not know any avalue for maxlenght
      // we assign by rule -1 (this mean maxlength can be any number[5 or 8 or 100 or ...])
      maxlength = -1;
    }
  else
    {
      minlength = vm["minlength"].as<int>(); //set minlength to the default value 0
      maxlength = vm["maxlength"].as<int>();
    }

  // password complexity requirements (mask section)

  // lower characters
  if(vm.count("minlower") && vm.count("maxlower"))
    {
      minlower = vm["minlower"].as<int>();
      maxlower = vm["maxlower"].as<int>();
      if((int)minlower > maxlower)
        throw "Ivalid paramemters";
    }
  else if(vm.count("minlower"))
    {
      minlower = vm["minlower"].as<int>();
      // Because we do not know any avalue for maxlower
      // we assign by rule -1 (this mean maxlower can be any number[5 or 8 or 100 or ...])
      maxlower = -1;
    }
  else
    {
      minlower = vm["minlower"].as<int>(); //set minlower to the default value 0
      maxlower = vm["maxlower"].as<int>();
    }

  // upper characters
  if(vm.count("minupper") && vm.count("maxupper"))
    {
      minupper = vm["minupper"].as<int>();
      maxupper = vm["maxupper"].as<int>();
      if((int)minupper > maxupper)
        throw "Ivalid paramemters";
    }
  else if(vm.count("minupper"))
    {
      minupper = vm["minupper"].as<int>();
      // Because we do not know any avalue for maxupper
      // we assign by rule -1 (this mean maxupper can be any number[5 or 8 or 100 or ...])
      maxupper = -1;
    }
  else
    {
      minupper = vm["minupper"].as<int>(); //set minupper to the default value 0
      maxupper = vm["maxupper"].as<int>();
    }

  // digit characters
  if(vm.count("mindigit") && vm.count("maxdigit"))
    {
      mindigit = vm["mindigit"].as<int>();
      maxdigit = vm["maxdigit"].as<int>();
      if((int)mindigit > maxdigit)
        throw "Ivalid paramemters";
    }
  else if(vm.count("mindigit"))
    {
      mindigit = vm["minidigt"].as<int>();
      // Because we do not know any avalue for maxdigit
      // we assign by rule -1 (this mean maxdigit can be any number[5 or 8 or 100 or ...])
      maxdigit = -1;
    }
  else
    {
      mindigit = vm["mindigit"].as<int>(); //set mindigit to the default value 0
      maxdigit = vm["maxdigit"].as<int>();
    }

  // special characters
  if(vm.count("minspecial") && vm.count("maxspecial"))
    {
      minspecial = vm["minspecial"].as<int>();
      maxspecial = vm["maxspecial"].as<int>();
      if((int)minspecial > maxspecial)
        throw "Ivalid paramemters";
    }
  else if(vm.count("minspecial"))
    {
      minspecial = vm["minspecial"].as<int>();
      // Because we do not know any avalue for maxspecial
      // we assign by rule -1 (this mean maxspecial can be any number[5 or 8 or 100 or ...])
      maxspecial = -1;
    }
  else
    {
      minspecial = vm["minspecial"].as<int>(); //set minspecial to the default value 0
      maxspecial = vm["maxspecial"].as<int>();
    }
}
