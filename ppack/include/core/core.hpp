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



#ifndef _PPACK_H
#define _PPACK_H


#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <omp.h>

using namespace std;


#include "mask.hpp"
#include "password.hpp"
#include "args.hpp"
#include "base.hpp"
#include "logos.hpp"
#include "csv.hpp"

class PPACK
{

public:

  PPACK(){}

  // using pstructs to pass paramether to static method of PPACK class

  static void statsgen(Sargs sargs);
  static void maskgen(Margs margs);
  static void policygen(Pargs pargs);

  // // core of statsgen
  // friend statstruct coreStatsgen(sstruct pargs);
  // friend void writeStatsgen(statstruct stats, sstruct pargs);
  // // core of policygen is in basepoli.cpp
};

#endif // _PPACK_H