/*
 * Mask class depuration
 * date: 24 nov 2020
 *
 * Mantainer: glozanoa <glozanoa@uni.pe>
 *
 */


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

using namespace std;

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../../include/mask.hpp"
#endif //__INCLUDE_MASK_H__


int main(int argc, char** argv)
{

  string smask = "?l?u?l?s?d?d";
  Mask mask(smask);

  cout << "privated members - mask(" << mask << ")" << endl;

  cout << "mstruct:" << endl;
  maskStruct mstruct = mask.getStruct();
  cout << "lowercases: " << mstruct.lowercase
       << "\nuppercases: " << mstruct.uppercase
       << "\nspecial   : " << mstruct.special
       << "\ndigits    : " << mstruct.digit << endl;

  cout << "\nCharset:" << endl;
  cout << "scs: " << mask.getValueSCS()
       << "\nacs: " << mask.getValueACS() << endl;


  // depuration of check functions

  // ismask check function
  cout << "\nismask function:" << endl;
  if(ismask(smask))
    cout << mask << " is a mask." << endl;
  else
    cout << mask << "is an invalid mask." << endl;

  // checkLength check function
  cout << "\ncheckLength function:" << endl;
  int minlength = 2;
  int maxlength = 4;
  if(checkLength(mask, minlength, maxlength))
    cout << "len(" << mask << "):" << mask.length() << " is between " << minlength << " and " << maxlength << endl;
  else
    cout << "Invalid len(" << mask << ") : " << mask.length() << endl;



  // parser functions
  cout << "\nscsParser function:" << endl;
  SCS scsMask = scsParser(mstruct);
  cout << "cssmMask: " << scsMask << endl;

  cout << "\nanalysis function:" << endl;

  Mask parserMask = Mask::analysis(smask);
  cout << "parserMask: " << parserMask << endl;

  return 0;
}
