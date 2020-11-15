#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include<iostream>
#endif //__INCLUDE_STD_IOSTREAM_H_

// #ifndef __INCLUDE_STD_STRING_H_
// #define __INCLUDE_STD_STRING_H_
// #include<string>
// #endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H_
#define __INCLUDE_STD_VECTOR_H_
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_

using namespace std;

// #ifndef __INCLUDE_MASK_H_
// #define __INCLUDE_MASK_H_
// #include "../include/mask.hpp"
// #endif //__INCLUDE_MASK_H_

#ifndef __INCLUDE_PPACK_H_
#define __INCLUDE_PPACK_H_
#include "../include/ppack.hpp"
#endif //__INCLUDE_PPACK_H_


// #ifndef __INCLUDE_BASE_H__
// #define __INCLUDE_BASE_H__
// #include "../include/base.hpp"
// #endif //__INCLUDE_BASE_H__



////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Policygen implementation /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


poliStruct init_polistruct(int minlength, int maxlength,                         //length parameters
                     int minlower, int maxlower,                           //
                     int minupper, int maxupper,                           // password
                     int mindigit, int maxdigit,                           // charset
                     int minspecial, int maxspecial)
{
  poliStruct pstruct;
  pstruct.minlength = minlength;
  pstruct.maxlength = maxlength;
  pstruct.minlower = minlower;
  pstruct.maxlower = maxlower;
  pstruct.minupper = minupper;
  pstruct.maxupper = maxupper;
  pstruct.mindigit = mindigit;
  pstruct.maxdigit = maxdigit;
  pstruct.minspecial = minspecial;
  pstruct.maxspecial = maxspecial;

  return pstruct;
}


string repeat(string str, int n)
{
  string repeat_str="";
  for(int k=0; k<n; k++)
    repeat_str += str;

  return repeat_str;
}




Base::Base(poliStruct init)
{
  bstruct = init;
  string init_mask;

  init_mask = repeat("?l", bstruct.minlower) +\
    repeat("?d", bstruct.minupper) +\
    repeat("?u", bstruct.minupper) +\
    repeat("?s", bstruct.minspecial);

  Mask initMask(init_mask);

  base = new vector<Mask>;
  base->push_back(initMask);
  length = 1;
}

Base::~Base()
{
  delete [] base;
}

void Base::appendMask(Mask step)
{
  base->push_back(step);
}

void Base::maskStep()
{
  vector<Mask> *step_base = new vector<Mask>;
  for(Mask mask : *base)
    {
      maskStruct mstruct = maskAnalysis(mask);

      if(mstruct.lowercase <= bstruct.maxlower)
        {
          step_base->push_back(mask + "?l");
          if(mstruct.digit <= bstruct.maxdigit)
              step_base->push_back(mask + "?d");

          if(mstruct.uppercase <= bstruct.maxupper)
              step_base->push_back(mask + "?u");

          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.digit <= bstruct.maxdigit)
        {
          step_base->push_back(mask + "?d");
          if(mstruct.uppercase <= bstruct.maxupper)
              step_base->push_back(mask + "u");
          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.uppercase <= bstruct.maxupper)
        {
          step_base->push_back(mask + "?u");
          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.special <= bstruct.maxspecial)
        {
          step_base->push_back(mask + "?s");
        }
    }

  // replace the updated base(step_base) with base
  delete [] base; // fre memory of base = vector<Mask>
  base = step_base;
  length += 1;
}

void permuteMasks(Base base)
/*
 * This function compute all the permutations without repetitions
 * and write all of them to a file.
 */
{
  cout << "search for a c++ function to do this work(permutations)" << endl;
}

void corePolicygen(poliStruct init)
{
  Base base(init);

  for(int len=base.getLength(); len < base.getPoliMinLength(); len++)
    {
      // generate all the posible mask with the required parameter
      // and increase the length of base in one
      base.maskStep();
    }

  // now the length of base is equal to minlength(policygen paramemter)
  for(int len=base.getLength(); len < base.getPoliMaxLength(); len++)
    {
      permuteMasks(base); // compute all the permutation of the mask(without repetitions)
      base.maskStep();
    }
}

static void policygen(string output,                       //Output File
                      bool quiet, bool show,                           //print parameters
                      int minlength, int maxlength,                         //length parameters
                      int minlower, int maxlower,                           //
                      int minupper, int maxupper,                           // password
                      int mindigit, int maxdigit,                           // charset
                      int minspecial, int maxspecial)
{
  poliStruct pstruct =  init_polistruct(minlength, maxlength,
                                      minlower, maxlower,
                                      minupper, maxupper,
                                      mindigit, maxdigit,
                                      minspecial, maxspecial);

  corePolicygen(pstruct); //do almost all the work()
  //  cout << "hello from policygen ppack's method" << endl;
}
