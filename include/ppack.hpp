/*
 * Definition of ppack class
 * statsgen method:  Compute statistis of a wordlist
 * maskgen methos:   Generate mask from the statistics generated by statsgen
 * policygen method: Generate a set of mask with some requirements
 *
 *
 * Reimplementation PPACK class - 25 nov 2020
 *
 * COMPLETE(pstructs.hpp implement rstruct class ans their ineheritance classes)
 * ---- Create a unique struct instead of have statstruct, maskgenStruct, poliStruct ---
 *
 *
 * Implmenetd PPACK - 23 nov 2020
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */



#ifndef __PPACK_H__
#define __PPACK_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_

using namespace std;

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H__


#ifndef __INCLUDE_PASSWORD_H__
#define __INCLUDE_PASSWORD_H__
#include "password.hpp"
#endif //__INCLUDE_PASSWORD_H__


#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "pstructs.hpp"
#endif //__INCLUDE_PSTRUCTS_H__





string PPACK_VERSION = "1.0";

class PPACK
{
// private:
//   static string wordlist_file;
//   static string output_statsgen;
//   static string output_maskgen;
//   static string output_policygen;

public:

  PPACK(){}
  // PPACK(){VERSION = "1.0";}
  //PPACK(string wordlist):wordlist_file{wordlist}{}


  // static void statsgen(string wordlist, string output,                           //IO parameters

  //               bool hiderare, bool quiet,                      //print parameters
  //               vector<string> charset,                            //password charset
  //                 int minlength, int maxlength);                         //length parameters



  //   static void maskgen(string statsgen_output, string output,    //IO parameters

  //               bool show, bool quiet,                           //print parameters
  //                vector<Mask> checkmasks,string checkmasksfile,       //checkmask parameters
  //               vector<string> charset,                            //password charset
  //               int minlength, int maxlength,                         //length parameters
  //               int mincomplexity, int maxcomplexity,                 //complexity parameters
  //                int minoccurrence, int maxoccurrence);                 //occurrence parameters




  // // this method depend of Base class
  // // and corePolicygen is the more important function(this function generate a new Base)
  // static void policygen(string output,                       //Output File
  //                       bool quiet, bool show,                           //print parameters
  //                       int minlength, int maxlength,                         //length parameters
  //                       int minlower, int maxlower,                           //
  //                       int minupper, int maxupper,                           // password
  //                       int mindigit, int maxdigit,                           // charset
  //                       int minspecial, int maxspecial);

  // using pstructs to pass paramether to static method of PPACK class

  static void statsgen(sstruct sargs);
  static void maskgen(mstruct margs);
  static void policygen(pstruct pargs);

};
#endif // __PPACK_H__
