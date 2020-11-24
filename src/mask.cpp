/*
 * Mask class implementation
 * Mask class reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__


#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H__


#ifndef __INCLUDE_MASK_EXCEPTIONS_H__
#define __INCLUDE_MASK_EXCEPTIONS_H__
#include "../include/mask_exceptions.hpp"
#endif //__INCLUDE_MASK_EXCEPTIONS_H__

#ifndef __INCLUDE_CHARACTER_H__
#define __INCLUDE_CHARACTER_H__
#include "../include/character.hpp"
#endif //__INCLUDE_CHARACTER_H__


#ifndef __INCLUDE_STD_IOSTREAM_H___
#define __INCLUDE_STD_IOSTREAM_H__
#include<iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

using namespace std;

//#include "omp.h"


// check methods
bool ismask(string mask);
bool checkLength(Mask mask, int minlength, int maxlength);
bool checkSCS(Mask mask, vector<SCS> scs); //check if mask have one of the simple Charset of scs
bool checkACS(Mask mask, vector<ACS> acs); //check if mask have one of the advance Charset of acs
bool checkComplexity(Mask mask, int minCompexity, int maxComplexity);
bool isMaskCharset(string maskCharset); // check if a symbols is a valid symbol mask

// modificator methods
void realloc(string masksymbol); // add a mask symbol to a mask and update mstruct
vector<Mask> permutations();


// change to void 23 nov
//  friend void maskAnalysis(Mask mask);
Mask analysis(string mask);
SCS parserSCS(Mask mask);



Mask::Mask(string mask)
  :string(mask) // NOTA: EL CONTRUCTOR DE LA CLASE PADRE (string) DEBE IR AQUI NO EN EL CUERPO SINO NO FUNCIONA.
{

  try{
    if(!ismask(mask))
      throw invalid_mask;

    // mask analysis
    for(int i=1; i<(int)mask.size(); i+=2)
      {
        switch(mask[i])
          {
          case 'l':
            this->realloc("?l");
            break;
          case 'd':
            this->realloc("?d");
            break;
          case 'u':
            this->realloc("?u");
            break;
          case 's':
            this->realloc("?s");
            break;
          }
      }

    SCS charset = scsParser(mstruct);
    complexity = 0; // implement a function to compute mask complexity
    advanceCharset = ACS::advnone; //init advanceCharset with none, use only the set method to get acs

  }
  catch(invalid_argument& error)
    {
      cerr << error.what() << endl;
    }
}




// check friend methods

bool ismask(string mask)
{
  bool master_ismask = true;
  //#pragma omp parallel for shared(master_ismask, maskSymbols)
  for(int k=1; k<(int)mask.size(); k+=2)
    {


      // if the string mask  isn't a mask, then only pass.
      if(!master_ismask)  continue;

      if(charset::masksymbols.find(mask[k], 0) == string::npos)
        {
          //#pragma omp critical
          master_ismask = false;
        }
    }
  return master_ismask;
}


bool checkLength(Mask mask, int minlength, int maxlength)
{
  if(mask.length() > minlength && mask.length() < maxlength)
    return true;
  return false;
}


// bool checkSCS(Mask mask, vector<SCS> charsets)
// {

//   // CHECK BUG
//   if(find(charsets.begin(), charsets.end(), mask.getSCS()) != charsets.end())
//      return true;
//   return false;
// }


// bool checkACS(Mask mask, vector<ACS> charsets)
// {

//   // CHECK BUG
//   if(find(charsets.begin(), charsets.end(), mask.getACS()) != charsets.end())
//      return true;
//   return false;
// }


bool checkComplexity(Mask mask, int minCompexity, int maxComplexity)
{
  int complexity = mask.getComplexity();
  if(complexity > minCompexity && complexity < maxComplexity)
    return true;
  return false;
}



bool isMaskCharset(string maskCharset) // check if a symbols is a valid symbol mask
{
  if(maskCharset.size() == 2)
    {
      if(charset::masksymbols.find(maskCharset[1], 0) == string::npos)
        return true;
    }
  return false;

}


// get and set methods
ACS Mask::getACS()
{
  if(advanceCharset != ACS::advnone)
    return advanceCharset;
  else
    {
      // compute the ASC and the return advanceCharset
      return advanceCharset;
    }
}

void Mask::realloc(string maskCharset)
{
  try{
    if(!isMaskCharset(maskCharset))
      throw invalid_maskcharset;

    if(maskCharset == "?l")
      mstruct.lowercase += 1;
    else if(maskCharset == "?u")
      mstruct.uppercase += 1;
    else if(maskCharset == "?d")
      mstruct.digit += 1;
    else // special maskCharset
      mstruct.special += 1;

    // finally add the maskChatset to the mask
    *this += maskCharset;
  }
  catch(exception& error)
    {
      cerr << error.what() << endl;
    }
  // catch (invalid_maskcharset &error)
  //   {
  //     cerr << error.what() << endl;
  //   }

}

// vector<Mask> Mask::permutations()
// {
//   // perform all the permutation of the mask
//   cout << "No forget implement permutation method(Mask Class)." << endl;
// }

Mask Mask::analysis(string mask)
{
  Mask gmask(""); // generate mask (empty)

  try{
    if(!ismask(mask))
      throw invalid_mask;

    //#pragma omp parallel for shared(mask)
    for(int i=1; i<(int)mask.size(); i+=2)
      {
        switch(mask[i])
          {
          case 'l':
            gmask.realloc("?l");
            break;
          case 'd':
            gmask.realloc("?d");
            break;
          case 'u':
            gmask.realloc("?u");
            break;
          case 's':
            gmask.realloc("?s");
            break;
          }
      }

    maskStruct mstruct = gmask.getStruct();
    gmask.setSCS(scsParser(mstruct));

    return gmask;
  }
    catch(exception& error)
      {
        cerr << error.what() << endl;
        return Mask("");
      }
}



SCS scsParser(maskStruct mstruct)
{
    // parse a maskStruct to determine the scs of the mask

    if(mstruct.lowercase &&
        !(mstruct.digit || mstruct.uppercase || mstruct.special))
        return SCS::loweralpha;

    else if(mstruct.uppercase &&
        !(mstruct.lowercase || mstruct.digit || mstruct.special))
        return SCS::numeric;

    else if(mstruct.digit &&
        !(mstruct.lowercase || mstruct.uppercase || mstruct.special))
        return SCS::numeric;

    else if(mstruct.special &&
        !(mstruct.lowercase || mstruct.uppercase || mstruct.digit))
        return SCS::numeric;

    else if((mstruct.uppercase && mstruct.lowercase) &&
        !(mstruct.uppercase || mstruct.digit))
        return SCS::alpha;

    else if((mstruct.special && mstruct.uppercase && mstruct.lowercase) &&
        !(mstruct.digit))
        return SCS::mixalphaspecial;

    else if((mstruct.digit && mstruct.special) &&
        !(mstruct.uppercase || mstruct.lowercase))
        return SCS::mixspecialnum;

    else if(mstruct.special && mstruct.lowercase && mstruct.uppercase && mstruct.digit)
        return SCS::mixall;

    else
        return SCS::none;
}
