/*
 * Base class definition - 25 nov 2020
 *
 *
 *
 * Depuration:
 *
 *
 *
 * No tested functions:
 *
 *
 * No implemented functions:
 *
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */


#ifndef __BASE_H__
#define __BASE_H__

#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "pstructs.hpp"
#endif //__INCLUDE_PSTRUCTS_H__



// base class of policygen
class Base
{
private:
  pstruct bstruct; // base struct , entered options for policygen
  vector<Mask> *base;
  unsigned int length;

public:

  Base(pstruct initial);
  void maskStep(); // generate all the posible mask of length = length +1(step)

  void appendMask(Mask step); // next step mask

  unsigned int getLength(){return length;}
  int numberMasks(){return base->size();}


  int getPoliMinLength(){return bstruct.minlength;}
  int getPoliMaxLength(){return bstruct.maxlength;}

  ~Base();
};

#endif //__BASE_H__
