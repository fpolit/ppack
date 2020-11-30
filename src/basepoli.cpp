/*
 * Base class implementation - 25 nov 2020
 *
 *
 *
 * Depuration: 
 * TESTED ALL THE FUNCTION with exeption of permuteMasks, 
 * because it isn't implemented yet. 
 *
 *
 * No tested functions: ALL FUNCTION TESTED
 *
 * No implemented functions:
 *  void permuteMasks(Base base)
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */

#ifndef __INCLUDE_BASE_H__
#define __INCLUDE_BASE_H__
#include "../include/basepoli.hpp"
#endif //__INCLUDE_BASE_H__

#ifndef __INCLUDE_FINEPRINT_H__
#define __INCLUDE_FINEPRINT_H__
#include "../include/fineprint.hpp"
#endif //__INCLUDE_FINEPRINT_H_



#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

//tested 27 nov 2020
string repeat(string str, int n)
{
  string repeat_str= "";
  for(int k=0; k<n; k++)
    repeat_str += str;

  return repeat_str;
}

Base::Base()
{
  length = 0;
  baseMasks = new vector<Mask>;
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
  delete  baseMasks;
}

void Base::appendMask(Mask step)
{
  baseMasks->push_back(step);
}

// tested 27 nov 2020
Base* maskStep(Base *base)
{
  unsigned int lengthBaseStep = base->getLength()+1;
  Base* baseStep = new Base(base->getBaseStruct(), lengthBaseStep);

  pstruct bstruct = base->getBaseStruct();
  for(Mask mask : base->getBaseMasks())
    {
      maskStruct mstruct = mask.getStruct();

      if(mstruct.lowercase < bstruct.maxlower || bstruct.maxlower == -1)
        {
          baseStep->appendMask(reallocMask(mask, "?l"));
          if(mstruct.digit < bstruct.maxdigit || bstruct.maxdigit == -1)
              baseStep->appendMask(reallocMask(mask, "?d"));

          if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
              baseStep->appendMask(reallocMask(mask, "?u"));

          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            baseStep->appendMask(reallocMask(mask, "?s"));
        }
      else if(mstruct.digit < bstruct.maxdigit || bstruct.maxdigit == -1)
        {
          baseStep->appendMask(reallocMask(mask, "?d"));
          if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
              baseStep->appendMask(reallocMask(mask, "?u"));
          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            baseStep->appendMask(reallocMask(mask, "?s"));
        }
      else if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
        {
          baseStep->appendMask(reallocMask(mask, "?u"));
          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            baseStep->appendMask(reallocMask(mask, "?s"));
        }
      else if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
        {
          baseStep->appendMask(reallocMask(mask, "?s"));
        }
    }

    delete base;
    return baseStep;
}

void Base::showMasks()
{
  cout << FinePrint::greenText("[+]") << " Base " << length << " :" << endl;
  for(auto mask: *baseMasks)
  {
    cout << "\t" << mask << endl;
  }
}

void permuteMasks(Base base)
/*
 * This function compute all the permutations without repetitions
 * and write all of them to a file.
 */
{
  cout << "Compute all the permutation without repetitions." << endl;
}

// compute a set of bases[PoliBase]
// (with length equal to minlength  till maxlength)
// tested 27 nov 2020 
void corePolicygen(pstruct init)
{
  Base *base = new Base(init);
  
  int minlength = base->getMinLength();
  int baseLength = base->getLength();
  while(baseLength < minlength - 1)
    {
      base = maskStep(base); //increase the length of base in one
      baseLength += 1;
    }


  // now the length of base is equal to minlength-1(policygen paramemter)
  vector<Base*>* basePoli = new vector<Base*>;
  if(init.show)
  {
    for(int step=base->getLength(); step < base->getMaxLength(); step++)
    {
      base->showMasks();
      //basePoli->push_back(base);
      base = maskStep(base);
      // HERE PRINT THE OUTPUT OR WRITE TO FILE. 
    }
    base->showMasks();
  }
  else
  {
    for(int step=base->getLength(); step < base->getMaxLength(); step++)
    {
      //base->showMasks();
      //basePoli->push_back(base);
      base = maskStep(base);
      // HERE PRINT THE OUTPUT OR WRITE TO FILE. 
    }
  //base->showMasks();
  }
  
  delete base;
}
