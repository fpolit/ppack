/*
 * pstruct ppack structs head file
 * pstruct implemented 24 nov 2020
 *
 *
 * Depuration:
 * rstruct and inheritance classes tested 27 nov 2020.
 *
 * No tested functions: ALL ClASES TESTED
 *
 * No implemented functions: ALL FUNCTIONS OR METHOD IMEPLEMENTED
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

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

#ifndef __INCLUDE_STD_CSTDLIB_H__
#define __INCLUDE_STD_CSTDLIB_H__
#include <cstdlib>
#endif //__INCLUDE_STD_CSTDLIB_H__

#ifndef __INCLUDE_STD_EXCEPTION_H__
#define __INCLUDE_STD_EXCEPTION_H__
#include <exception>
#endif //__INCLUDE_STD_EXCEPTION_H__

using namespace std;

#ifndef __INCLUDE_PROGRAM_OPTIONS_H__
#define __INCLUDE_PROGRAM_OPTIONS_H__
#include<boost/program_options.hpp>
#endif //__INCLUDE_PROGRAM_OPTIONS_H__

using namespace boost;
namespace po = boost::program_options;

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif // __INCLUDE_MASK_H__

#ifndef __INCLUDE_OMP_H__
#define __INCLUDE_OMP_H__
#include "omp.h"
#endif //__INCLUDE_OMP_H__

// #ifndef __INCLUDE_SIMPLEINI_H__
// #define __INCLUDE_SIMPLEINI_H__
// #include "simpleini/SimpleIni.h"
// #endif // __INCLUDE_SIMPLEINI_H__


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


// requirement struct (maskgen and policygen requirements)
class rstruct
{
public:
  rstruct(){};
  rstruct(unsigned int min_length, int max_length,
          bool quietPrint,
          string outputFile, string inputFile,
          unsigned int nthreads);

  // password and mas structure requirements
  unsigned int minlength;
  int maxlength;

  // print requirements
  bool quiet;
  bool pretty;

  // io parameters
  string input; // input file
  string output; //output file

  // parallel parameters
  unsigned int threads;

  virtual void debug();
  ~rstruct(){}
};

// statsgen requirements struct
class sstruct: public rstruct
{
public:
  sstruct(po::variables_map vm, po::options_description statsgen);
  sstruct(unsigned int min_length, int max_length, //mask struct parameters
          bool quiet_print, double hide_rare,          //print parameters
          string output_file, string input_file,     // IO parameters
          vector<string> scharsets, 
          vector<string> acharsets,                  // check parameters
          unsigned int nthreads);


  // password and mas structure requirements
  //unsigned int minlength; - inheritance attribute
  //int maxlength; - inheritance attribute


  // print parameters
  double hiderare;
  // bool quiet; - inheritance attribute

  // check requierement
  vector<SCS> scs;
  vector<ACS> acs;


  // io parameters
  string wordlist; // wordlist file
  // string input; // input options - inehritance attribute
  // string output; //output file of statsgen - inehritance attribute

  void debug();
};


// maskgen requirements struct
class mstruct: public rstruct
{
public:
  mstruct(po::variables_map vm, po::options_description maskgen);
  mstruct(unsigned int min_length, int max_length,             //
          unsigned int min_complexity, int max_complexity,     // mask struct parameters
          unsigned int min_occurence, int max_occurence,       //
          bool quiet_print, bool show_masks,                   // print parametersxs
          vector<string> scharsets, vector<string> acharsets,
          vector<Mask> checkmasks,string checkmasksfile,
          string output_file, string statgen_ouput,
          unsigned int nthreads);

  // password and mas structure requirements
  //unsigned int minlength; - inheritance attribute
  //int maxlength; - inheritance attribute
  unsigned int mincomplexity;
  int maxcomplexity;

  unsigned int minoccurrence;
  int maxoccurrence;

  // print parameters
  bool show;
  // bool quiet; - inheritance attribute

  // check requierement
  vector<Mask> checkMasks;
  string checkMaskFile;
  vector<SCS> scs;
  vector<ACS> acs;

  // io paramemters
  //string input; // input options - inehritance attribute
  //string output; //output file of maskgen (generated masks) - inehritance attribute
  string statsgen; // output of statsgen method 

  void debug();
};


// policygen requirements struct
class pstruct:public rstruct
{
public:
  pstruct(){};
  pstruct(po::variables_map vm, po::options_description policygen);
  pstruct(unsigned int min_length, int max_length,    //
                 unsigned int min_lower, int max_lower,      // masks
                 unsigned int min_upper, int max_upper,      // struct
                 unsigned int min_digit, int max_digit,      // parameters
                 unsigned int min_special, int max_special,  // 
                 bool quiet_print, bool show_masks,          // print parameters
                 string output_file, string input_file,      // io parameters
                 unsigned nthreads);

  // password and mas structure requirements
  //unsigned int minlength; - inehritance attribute
  //int maxlength; - inehritance attribute
  unsigned int minlower;
  int maxlower;

  unsigned int minupper;
  int maxupper;

  unsigned int mindigit;
  int maxdigit;

  unsigned int minspecial;
  int maxspecial;

  // unsigned int mincomplexity;
  // int maxcomplexity;

  // print requirements
  //bool quiet; - inehritance attribute
  bool show;

  // io paramemters
  //string input; // requirement file - inehritance attribute
  //string output; //output file of policygen (generated masks) --inheritance attribute

  void debug(); // show all the parameters
};


// statgen stats struct (property , occurence)
typedef struct statstruct
{
  unsigned long total=0; //total number of analyzed passwords
  map<SCS, int> scs;
  map<Mask, int> mask;
  map<unsigned int, int> length;
}statstruct;

#endif //__PSTRUCTS_H__
