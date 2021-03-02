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

  if(Mask::ismask(smask))
    cout << smask << " is a mask." << endl;
  else
    cout << smask << " isn't  a mask." << endl;

  return 0;
}
