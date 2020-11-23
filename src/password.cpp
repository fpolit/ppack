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

            if(CharSet.islower(letther))
            {
              maskParser.realloc("?l");
            }
            else if(isupper(letther))
            {
              maskParser.realloc("?u");
            }
            else if(isdigit(letther))
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




Password::Password(string passwd)
  :string(passwd)
{
  mask = analyzePassword(passwd);
}
