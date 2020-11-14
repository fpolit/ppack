#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include<iostream>
#endif //__INCLUDE_STD_IOSTREAM_H_

// #ifndef __INCLUDE_STD_STRING_H_
// #define __INCLUDE_STD_STRING_H_
// #include<string>
// #endif //__INCLUDE_STD_STRING_H_

// #ifndef __INCLUDE_STD_VECTOR_H_
// #define __INCLUDE_STD_VECTOR_H_
// #include<vector>
// #endif // __INCLUDE_STD_VECTOR_H_

using namespace std;

// #ifndef __INCLUDE_MASK_H_
// #define __INCLUDE_MASK_H_
// #include "../include/mask.hpp"
// #endif //__INCLUDE_MASK_H_

#ifndef __INCLUDE_PPACK_H_
#define __INCLUDE_PPACK_H_
#include "../include/ppack.hpp"
#endif //__INCLUDE_PPACK_H_


#ifndef __INCLUDE_BASE_H__
#define __INCLUDE_BASE_H__
#include "../include/base.hpp"
#endif //__INCLUDE_BASE_H__



////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Policygen implementation /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


poliStruct init_polystruct(int minlength, int maxlength,                         //length parameters
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

// Base corePolicygen(Base init_base)
// {

// }

static void policygen(string output,                       //Output File
                      bool quiet, bool show,                           //print parameters
                      int minlength, int maxlength,                         //length parameters
                      int minlower, int maxlower,                           //
                      int minupper, int maxupper,                           // password
                      int mindigit, int maxdigit,                           // charset
                      int minspecial, int maxspecial)
{
  poliStruct pstruct =  init_polystruct(minlength, maxlength,
                                      minlower, maxlower,
                                      minupper, maxupper,
                                      mindigit, maxdigit,
                                      minspecial, maxspecial);

  Base init_base(pstruct);



  //  cout << "hello from policygen ppack's method" << endl;
}
