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

typedef struct baseStruct
{
  unsigned int minlength  = 0;
  unsigned int minlower   = 0;
  unsigned int minupper   = 0;
  unsigned int mindigit   = 0;
  unsigned int minspecial = 0;
  int maxlength  = 0;
  int maxlower   = 0;
  int maxupper   = 0;
  int maxdigit   = 0;
  int maxspecial = 0;
}baseStruct;

class Base
{
private:
  baseStruct bstruct; // base struct , entered options for policygen
  vector<Mask> masks;
  unsigned int length;

public:
  Base();
  Base(baseStruct initial);
  Base(baseStruct initial, unsigned int base_length);
  // generate a new base from a base increasing in 1 the length.
  friend Base mask_step(Base base);

  void append_mask(Mask step); // next step mask

  // get and set methods
  unsigned int get_length(){return length;}
  int count_masks(){return masks.size();}
  int get_minlength(){return bstruct.minlength;}
  int get_maxlength(){return bstruct.maxlength;}
  Mask get_mask(int k);
  vector<Mask> get_masks(){return masks;}
  baseStruct get_base_struct(){return bstruct;}

  //IO methods
  void show_masks();
  void permute_base(Base base, ofstream* outputPolicygen)
};

  //void permuteMasks(Base base);
  //void corePolicygen(pstruct init); //bases without permutations

#endif //_BASE_H
