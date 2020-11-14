
#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__


#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H__

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

Character characters;
//string maskSymbols = characters.masksymbol

bool ismask(string mask)
{
    bool master_ismask = true;
    string maskSymbols = characters.masksymbols;
    //#pragma omp parallel for shared(master_ismask, maskSymbols)
    for(int k=1; k<mask.size(); k+=2)
    {


        // if the string mask  isn't a mask, then only pass.
        if(!master_ismask)  continue;

        if(maskSymbols.find(mask[k], 0) == string::npos)
        {
          //#pragma omp critical
                master_ismask = false;
        }
    }
    return master_ismask;
}

bool ismasksymbol(string masksymbol) // check if a symbols is a valid symbol mask
{
  if(masksymbol.size() == 2)
    {
      string maskSymbols = characters.masksymbols;
      if(maskSymbols.find(masksymbol[1], 0) == string::npos)
        return true;
    }
  return false;

}
// START: Mask class implementation


Mask::Mask(string mask)
  :string(mask) // NOTA: EL CONTRUCTOR DE LA CLASE PADRE (string) DEBE IR AQUI NO EN EL CUERPO SINO NO FUNCIONA.
{
  //verify that mask have the format of a MASK
  if(ismask(mask)){
    //string(mask);
    cout << mask << " is a mask." << endl;
  }
  else{
    throw "Invalid mask: " + mask;
  }
}


void Mask::expand(string masksymbol)
{
  if(ismasksymbol(masksymbol))
    *this += masksymbol;
  else
    cout << masksymbol << " isn't a symbol mask." << endl;
}

// vector<Mask> Mask::permutations()
// {
//   // perform all the permutation of the mask
//   cout << "No forget implement permutation method(Mask Class)." << endl;
// }

// maskStruct maskAnalysis(Mask mask)
// {
//   maskStruct mask_struct;
// #pragma omp parallel for shared(mask)
//   for(int i=1; i<mask.size(); i+=2)
//     {
//     switch(mask[i])
//       {
//       case 'l':
//         mask_struct.lowercase += 1;
//       case "d":
//         mask_struct.digit += 1;
//       case "u":
//         mask_struct.uppercase += 1;
//       case "s":
//         mask_struct.special += 1;
//       }
//     }

//   return mask_struct;
// }
// END: Mask class implementation
