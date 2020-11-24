/*
 * Password class implementarion
 * Password class reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

using namespace std;

#ifndef __INCLUDE_PASSWORD_H__
#define __INCLUDE_PASSWORD_H__
#include "../include/password.hpp"
#endif //__INCLUDE_PASSWORD_H__

#ifndef __INCLUDE_CHARACTER_H__
#define __INCLUDE_CHARACTER_H__
#include "../include/character.hpp"
#endif //__INCLUDE_CHARACTER_H__

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif // __INCLUDE_MASK_H__

#ifndef __INCLUDE_OMP_H__
#define __INCLUDE_OMP_H__
#include "omp.h"
#endif //__INCLUDE_OMP_H__


Mask  analyzePassword(string passwd);


Password::Password(string password)
  :string(password)
{
  mask = analyzePassword(password);
}


Mask  analyzePassword(string passwd)
{
    string master_mask = "";

    Mask maskParser(master_mask);
    // computer the mask of the password and fill the maskStruct
    // #pragma omp parallel for ordered \
    //     shared(master_mask, passwd, symbols, passwdStruct)
    for(int k=0; k<passwd.size(); k++)
    {
      //#pragma omp ordered
        {
            string letther = to_string(passwd[k]);

            if(charset::islower(letther))
            {
              maskParser.realloc("?l");
            }
            else if(charset::isupper(letther))
            {
              maskParser.realloc("?u");
            }
            else if(charset::isdigit(letther))
            {
              maskParser.realloc("?d");
            }
            else //the character is a special character
            {
              maskParser.realloc("?s");
            }
        }
    }
    maskStruct mstruct = maskParser.getStruct();
    maskParser.setSCS(scsParser(mstruct));

    return maskParser;
}



