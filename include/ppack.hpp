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

#ifndef __INCLUDE_STD_CSTDLIB_H__
#define __INCLUDE_STD_CSTDLIB_H__
#include <cstdlib>
#endif //__INCLUDE_STD_CSTDLIB_H__

#ifndef __INCLUDE_STD_EXCEPTION_H__
#define __INCLUDE_STD_EXCEPTION_H__
#include <exception>
#endif //__INCLUDE_STD_EXECPTION_H__

#ifndef __INCLUDE_STD_IOMANIP_H__
#define __INCLUDE_STD_IOMANIP_H__
#include <iomanip>
#endif //__INCLUDE_STD_IOMANIP_H__

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include<iostream>
#endif //__INCLUDE_STD_IOSTREAM_H_

#ifndef __INCLUDE_FSTREAM_H__
#define __INCLUDE_FSTREAM_H__
#include<fstream>
#endif //__INCLUDE_FSTREAM_H__

#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H__

using namespace std;


#ifndef __INCLUDE_OMP_H__
#define __INCLUDE_OMP_H__
#include "omp.h"
#endif //__INCLUDE_OMP_H__



#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif //__INCLUDE_MASK_H__


#ifndef __INCLUDE_PASSWORD_H__
#define __INCLUDE_PASSWORD_H__
#include "password.hpp"
#endif //__INCLUDE_PASSWORD_H__


#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "pstructs.hpp"
#endif //__INCLUDE_PSTRUCTS_H__

#ifndef __INCLUDE_BASE_H__
#define __INCLUDE_BASE_H__
#include "basepoli.hpp"
#endif //__INCLUDE_BASE_H__

#ifndef __INCLUDE_LOGOS_H__
#define __INCLUDE_LOGOS_H__
#include "logos.hpp"
#endif //__INCLUDE_LOGOS_H__


#ifndef __INCLUDE_FINEPRINT_H__
#define __INCLUDE_FINEPRINT_H__
#include "fineprint.hpp"
#endif //__INCLUDE_FINEPRINT_H_


#ifndef __INCLUDE_CSV_H__
#define __INCLUDE_CSV_H__
#include "csv.hpp"
#endif //__INCLUDE_CSV_H__




class PPACK
{

public:

  PPACK(){}

  // using pstructs to pass paramether to static method of PPACK class

  static void statsgen(sstruct sargs);
  static void maskgen(mstruct margs);
  static void policygen(pstruct pargs);

  // core of statsgen
  friend statstruct coreStatsgen(sstruct pargs);
  friend void writeStatsgen(statstruct stats, sstruct pargs);
  // core of policygen is in basepoli.cpp
};
#endif // __PPACK_H__
