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
#include <exception>
#include <fstream>
#include <ostream>
#endif //__INCLUDE_BASE_H__



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

// check is base have a mask with similar structure of baseMask
// bool isDuplicateBaseMask(Base base, Mask mask)
// {
//   for(auto bmask: base.getBaseMasks())
//   {
//     if(Mask::equalStruct(bmask, mask))
//       return true;
//   }
//   return false;
// }


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

void Base::showMasks(bool prettyOutput)
{
  if(prettyOutput)
    cout << FinePrint::greenText("[+]") << " Base " << length << " :" << endl;
  else
   cout << "[+] Base " << length << " :" << endl;
  
  for(auto mask: *baseMasks)
  {
    cout << "\t" << mask << endl;
  }
}
Mask Base::getMask(int k)
{
  return baseMasks->at(k);
}

void writeMasks(Base* base, ofstream* outputPolicygen)
/*
 * This function compute all the permutations without repetitions
 * and write all of them to a file.
 */
{
  vector<Mask> baseMasks;
  for(int k=0; k<base->getNumberMasks(); k++)
  {
    Mask kmask = base->getMask(k);
    bool repeatMask = false;
#pragma omp parallel for shared(repeatMask, kmask, base)
    for(int i=k+1; i<base->getNumberMasks(); i++)
    {
      if(repeatMask) continue;
      Mask imask = base->getMask(i);
      
      if(Mask::equalStruct(kmask, imask))
        repeatMask = true;
    }
    if(!repeatMask)
      baseMasks.push_back(kmask);
  }

#pragma omp parallel for shared(baseMasks)
  for(int k=0; k<baseMasks.size(); k++)
  {
    Mask mask = baseMasks.at(k);
    string maskSymbols = mask.getSymbols();
    string smask;
    do {
      smask = "";
      for(auto character: maskSymbols)
          smask += "?" + string(1,character);
      #pragma omp critical
      *outputPolicygen << smask << endl;
    } while ( std::next_permutation(maskSymbols.begin(),maskSymbols.end()) );

    smask = "";
    for(auto character: maskSymbols)
      smask += "?" + string(1,character);

    #pragma omp critical
    *outputPolicygen << smask << endl;
  }
}

// compute a set of bases[PoliBase]
// (with length equal to minlength  till maxlength)
// tested 27 nov 2020 
void corePolicygen(pstruct pargs)
{
  Base *base = new Base(pargs);
  
  int minlength = base->getMinLength();
  int baseLength = base->getLength();
  while(baseLength < minlength - 1)
    {
      base = maskStep(base); //increase the length of base in one
      baseLength += 1;
    }


  // now the length of base is equal to minlength-1(policygen paramemter)
  vector<Base*>* basePoli = new vector<Base*>;
  if(pargs.show)
  {
    ofstream* outputPolicygen = new ofstream;
    outputPolicygen->open(pargs.output);
    try {
#pragma omp parallel for shared(base, outputPolicygen) ordered
      for(int step=base->getLength(); step < base->getMaxLength(); step++)
      {
        #pragma omp ordered
        base->showMasks(pargs.pretty);

        base = maskStep(base);
        writeMasks(base, outputPolicygen);
      }
      base->showMasks(pargs.pretty);
      writeMasks(base, outputPolicygen);
      outputPolicygen->close();

      if(pargs.pretty)
        FinePrint::successful("Generated masks have written in [" + pargs.output + "]");
      else
       cout << "Generated masks have written in [" + pargs.output + "]" << endl;

    } catch (std::exception& error) {
      cout << error.what() << endl;
      outputPolicygen->close();
    }
  }
  else
  {

    ofstream* outputPolicygen = new ofstream;
    outputPolicygen->open(pargs.output);
    try {
      for(int step=base->getLength(); step < base->getMaxLength(); step++)
      {
        base = maskStep(base);
        writeMasks(base, outputPolicygen);
      }
      writeMasks(base, outputPolicygen);
      outputPolicygen->close();
      
      if(pargs.pretty)
        FinePrint::successful("Generated masks have written in [" + pargs.output + "]");
      else
       cout << "Generated masks have written in [" + pargs.output + "]" << endl;
    } catch (std::exception& error) {
      cout << error.what() << endl;
      outputPolicygen->close();
    }
  }
  delete base;
}
