/*
 * Base class definition - 25 nov 2020
 *
 *
 *
 * Depuration: 
 * TESTED ALL THE FUNCTION with exeption of permuteMasks, 
 *  because it isn't yet implemented. 
 *
 * No tested functions: ALL FUNCTION TESTED
 *
 * No implemented functions:
 *  void permuteMasks(Base base)
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */

#ifndef _BASE_H
#define _BASE_H

#include <iostream>
#include <vector>

using namespace std;

#include "mask.hpp"
#include "args.hpp"

class Base
{
private:
  pstruct bstruct; // base struct , entered options for policygen
  vector<Mask> *masks;
  unsigned int length;

public:
  Base();
  Base(pstruct initial);
  Base(pstruct poliOpt, unsigned int len);
  // generate a new base from a base increasing in 1 the length.
  friend Base* maskStep(Base* base);

  void appendMask(Mask step); // next step mask

  // get and set methods
  unsigned int getLength(){return length;}
  int getNumberMasks(){return baseMasks->size();}
  int getMinLength(){return bstruct.minlength;}
  int getMaxLength(){return bstruct.maxlength;}
  Mask getMask(int k);
  vector<Mask> getBaseMasks(){return *baseMasks;}
  pstruct getBaseStruct(){return bstruct;}

  //show baseMasks
  void showMasks(bool prettyOutput);

  ~Base();
};

  //void permuteMasks(Base base);
  //void corePolicygen(pstruct init); //bases without permutations

#endif //_BASE_H
