#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H__

#ifndef __INCLUDE_CHARACTER_H__
#define __INCLUDE_CHARACTER_H__
#include "../include/character.hpp"
#endif //__INCLUDE_CHARACTER_H__


#include "omp.h"

Character characters;

bool ismask(string mask)
{
    bool master_ismask = true;
    #pragma omp parallel for shared(master_ismask) 
    for(int k=1; k<mask.size(); k+=2)
    {
        string maskSymbols = characters.masksymbols;

        // if the string mask  isn't a mask, then only pass.
        if(!master_ismask)  continue;

        if(maskSymbols.find(mask[k], 0) == string::npos)
        {
            #pragma omp critical
                master_ismask = false;
        }         
    }
    
    return master_ismask;
}


// START: Mask class implementation


Mask::Mask(string mask)
{
  //verify that mask have the format of a MASK
  if(ismask(mask)){
    string(mask);
  }
  else{
    throw "Invalid mask: " + mask;
  }
}


size_t Mask::size() const
{
  //    string mask_value = *this;
  //return mask_value.size()/2;
  return this->size()/2;
}

// bool Mask::ismasksymbol(string letther)
// {
//     string maskSymbols = characters.masksymbols;
//     if (maskSymbols.find(letther) == string::npos)
//     {
//         return false;
//     }
//     return true;
// }

// END: Mask class implementation
