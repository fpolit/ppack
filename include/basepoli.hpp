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
  vector<Mask> *baseMasks;
  unsigned int length;

public:
  
  Base(pstruct initial);
  Base(pstruct poliOpt, unsigned int len);
  // generate a new base from a base increasing in 1 the length. 
  friend Base maskStep(Base base); 

  void appendMask(Mask step); // next step mask

  unsigned int getLength(){return length;}
  int numberMasks(){return baseMasks->size();}


  int getMinLength(){return bstruct.minlength;}
  int getMaxLength(){return bstruct.maxlength;}
  
  vector<Mask> getBaseMasks(){return *baseMasks;}
  pstruct getBaseStruct(){return bstruct;}

  ~Base();
};

// class PoliBase
// // this class is equal to Base, but hasn't the pstruct(bstruct) attribute. 
// {
//   private:
//   vector<Mask> *baseMasks;
//   unsigned int length;

//   public:
//   PoliBase(Base base)
//   {
//     baseMasks = base.baseMasks;
//     length = base.length;
//   }
// }

//void permuteMasks(Base base);
vector<Base> corePolicygen(pstruct init); //bases without permitations

#endif //__BASE_H__
