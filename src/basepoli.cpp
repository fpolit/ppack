/*
 * Base class implementation - 25 nov 2020
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

#ifndef __INCLUDE_BASE_H__
#define __INCLUDE_BASE_H__
#include "../include/basepoli.hpp"
#endif //__INCLUDE_BASE_H__


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__


string repeat(string str, int n)
{
  string repeat_str= "";
  for(int k=0; k<n; k++)
    repeat_str += str;

  return repeat_str;
}


Base::Base(pstruct initial)
{
  bstruct = initial;
  string init_mask = "";

  init_mask += repeat("?l", bstruct.minlower);
  init_mask += repeat("?u", bstruct.minupper);
  init_mask += repeat("?s", bstruct.minspecial);
  init_mask += repeat("?d", bstruct.mindigit);


  Mask initMask(init_mask);

  baseMasks = new vector<Mask>;
  baseMasks->push_back(initMask);
  length = initMask.length();
}
// create a base of mask of length len and a empty baseMasks vertor.
Base::Base(pstruct poliOpt, unsigned int len)
{
  bstruct = poliOpt;
  length = len;
  baseMasks = new vector<Mask>;
}

Base::~Base()
{
  delete [] baseMasks;
}

void Base::appendMask(Mask step)
{
  baseMasks->push_back(step);
}

Base maskStep(Base base)
{
  // creation of the base baseJump (base of masks with length + 1)
  // this base is generated from the original base(masks are extended with a maskSymbol).
  unsigned int stepBaseLength = base.getLength() + 1;
  Base baseJump(base.getBaseStruct(), stepBaseLength);

  for(Mask mask : base.getBaseMasks())
    {
      maskStruct mstruct = mask.getStruct();
      pstruct bstruct = base.getBaseStruct();

      if(mstruct.lowercase < bstruct.maxlower || bstruct.maxlower == -1)
        {
          baseJump.appendMask(reallocMask(mask, "?l"));
          if(mstruct.digit < bstruct.maxdigit || bstruct.maxdigit == -1)
              baseJump.appendMask(reallocMask(mask, "?d"));

          if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
              baseJump.appendMask(reallocMask(mask, "?u"));

          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            baseJump.appendMask(reallocMask(mask, "?s"));
        }
      else if(mstruct.digit < bstruct.maxdigit || bstruct.maxdigit == -1)
        {
          baseJump.appendMask(reallocMask(mask, "?d"));
          if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
              baseJump.appendMask(reallocMask(mask, "?u"));
          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            baseJump.appendMask(reallocMask(mask, "?s"));
        }
      else if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
        {
          baseJump.appendMask(reallocMask(mask, "?u"));
          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            baseJump.appendMask(reallocMask(mask, "?s"));
        }
      else if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
        {
          baseJump.appendMask(reallocMask(mask, "?s"));
        }
    }
  
  return baseJump;
}


void permuteMasks(Base base)
/*
 * This function compute all the permutations without repetitions
 * and write all of them to a file.
 */
{
  cout << "Compute all the permutation without repetitions." << endl;
}

// return a set of bases[PoliBase]
// (with length equal to minlength  till maxlength)
vector<Base> corePolicygen(pstruct init)
{
  Base base(init);

  for(int len=base.getLength(); len < base.getMinLength()-1; len++)
      base = maskStep(base); //increase the length of base in one

  // now the length of base is equal to minlength-1(policygen paramemter)
  vector<Base> poliBases;
  for(int len=base.getLength(); len < base.getMaxLength(); len++)
    {
      base = maskStep(base);
      poliBases.push_back(base);
    }

  return poliBases; 
}
