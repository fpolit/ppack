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


// BEGIN: Password class implementation

Password::Password(string passwd)
  :string(passwd)
{
  Mask mask_passwd = analyzePassword(passwd, &passwdStruct);
  mask = mask_passwd;
  simple = detSimpleCS(passwdStruct);
  advance = ACS::none;
}


string Password::scs()
{
    return SimpleCharSet[simple];    
}

// string Password::acs()
// {
// // if (characters != "")
// //     return characters;
// // else
// // {
// //     LetterMask symbolsMask;
// //     map<string, unsigned int> simple{
// //         {"lowercase", 0},
// //         {"uppercase", 0},
// //         {"special", 0},
// //         {"digit", 0}
// //     };
// //     for(int k=1; k<2*mask.size(); k+=2)
// //     {
// //         string letter_mask = to_string(mask[k]);
// //         if(letter_mask == symbolsMask.lowercase)
// //             simple["lowercase"] += 1;

// //     }
// // }
// }

// int Password::complexity()
// {
//   return 0;
// }

// END: Password class implementation


// BEGIN: analyzePassword function implementation
Mask analyzePassword(string passwd, PStruct *pStruct)
{
    string master_mask = "";
    maskSymbols symbols;
    #pragma omp parallel for ordered \
        shared(master_mask, passwd, symbols, passwdStruct)
    for(int k=0; k<passwd.size(); k++)
    {
        #pragma omp ordered
        {
            string letther = to_string(passwd[k]);

            if(islower(letther))
            {
                master_mask += symbols.lowercase;
                pStruct->lowercase += 1;
            }
            else if(isupper(letther))
            {
                master_mask += symbols.uppercase;
                pStruct->uppercase += 1;
            }
            else if(isdigit(letther))
            {
                master_mask += symbols.digit;
                pStruct->digit += 1;
            }
            else
            {
                master_mask += symbols.special;
                pStruct->special += 1;
            }
        }
    }
    return Mask(master_mask);
}
// END: analyzePassword function implementation

// END: setSimpleCS function implementation

SCS detSimpleCS(PStruct pStruct)
{
    // determine the set of characteres that confor the password (simple Character Set)
    
    
    if(pStruct.lowercase &&
        !(pStruct.digit || pStruct.uppercase || pStruct.special))
        return SCS::loweralpha;

    else if(pStruct.uppercase &&
        !(pStruct.lowercase || pStruct.digit || pStruct.special))
        return SCS::numeric;

    else if(pStruct.digit &&
        !(pStruct.lowercase || pStruct.uppercase || pStruct.special))
        return SCS::numeric;

    else if(pStruct.special &&
        !(pStruct.lowercase || pStruct.uppercase || pStruct.digit))
        return SCS::numeric;

    else if((pStruct.uppercase && pStruct.lowercase) &&
        !(pStruct.uppercase || pStruct.digit))
        return SCS::alpha;
    
    else if((pStruct.special && pStruct.uppercase && pStruct.lowercase) &&
        !(pStruct.digit))
        return SCS::mixalphaspecial;

    else if((pStruct.digit && pStruct.special) &&
        !(pStruct.uppercase || pStruct.lowercase))
        return SCS::mixspecialnum;
    
    else if(pStruct.special && pStruct.lowercase && pStruct.uppercase && pStruct.digit)
        return SCS::mixall;

    else
        return SCS::none;
}
