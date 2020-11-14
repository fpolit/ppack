#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include<iostream>
#endif //__INCLUDE_STD_IOSTREAM_H_

#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H_
#define __INCLUDE_STD_VECTOR_H_
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_
using namespace std;

#ifndef __INCLUDE_MASK_H_
#define __INCLUDE_MASK_H_
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H_


#ifndef __INCLUDE_PPACK_H_
#define __INCLUDE_PPACK_H_
#include "../include/ppack.hpp"
#endif //__INCLUDE_PPACK_H_


// void PPACK::policygen(string output="complexity.hcmask",                       //Output File
//                bool quiet=false, bool show=true,                           //print parameters
//                int minlength=-1, int maxlength=-1,                         //length parameters
//                int minlower=-1, int maxlower=-1,                           //
//                int minupper=-1, int maxupper=-1,                           // password
//                int mindigit=-1, int maxdigit=-1,                           // charset
//                int minspecial=-1, int maxspecial=-1,                       //
//                unsigned int threads=2)                                    //parallel parameters
// {
//   cout << "hello polycigen" << endl;
// }

void PPACK::policygen(string output,                       //Output File
               bool quiet, bool show,                           //print parameters
               int minlength, int maxlength,                         //length parameters
               int minlower, int maxlower,                           //
               int minupper, int maxupper,                           // password
               int mindigit, int maxdigit,                           // charset
               int minspecial, int maxspecial,                       //
               unsigned int t)
{
  cout << "hello from policygen ppack's method" << endl;
}
