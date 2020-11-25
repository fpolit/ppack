/*
 * Password class implementarion
 * Password class reimplemented 23 nov 20202
 *
 *
 * Depuration:
 * Passowrd class tested 24 nov 2020.
 *
 *
 * No tested functions:
 *
 *
 *
 * No implemented functions:
 * vector<Mask> Mask::permutations();
 *
 * Warning:
 *
 * SOLVED - 24 nov 2020
 * ---- functions isSOMTHING problems <> 24 nov 2020 ----
 * isSOMETHING(work of with string of length 1) but function PERMIT string of length greater than 1,
 * in such case implement a loop over all the letther in that word and return true
 * if all the letthers are of SOMETHING type.
 *
 *
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


// #ifndef __INCLUDE_CHARACTER_H__
// #define __INCLUDE_CHARACTER_H__
// #include "../include/character.hpp"
// #endif //__INCLUDE_CHARACTER_H__

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif // __INCLUDE_MASK_H__


#ifndef __INCLUDE_OMP_H__
#define __INCLUDE_OMP_H__
#include "omp.h"
#endif //__INCLUDE_OMP_H__


// character.hpp
namespace charset{

  string ascci_letters =  R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string ascii_lowercase = R"(abcdefghijklmnopqrstuvwxyz)";
  string ascii_uppercase = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string digits = R"(0123456789)";
  string special = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
}


// head of functions
bool isdigit(string word);
bool islower(string word);
bool isupper(string word);
bool isspecial(string word);
Mask  analyzePassword(string passwd);


// tested - 24 nov 2020
bool isdigit(string word)
/*
 * verify if a word id only of digits or if a letther(word of one character) is a digit
 */
{
  for(auto letther: word)
    {
      if (charset::digits.find(letther) == string::npos)
        return false;
    }
  return true;
}

// tested - 24 nov 2020
bool islower(string word)
/*
 * verify if a word is only lowercase or if a letther(word of one character) is a lowercase
 */
{

  for(auto letther: word)
    {
      if (charset::ascii_lowercase.find(letther) == string::npos)
        return false;
    }
  return true;
}

// tested - 24 nov 2020
bool isupper(string word)
/*
 * verify if a word is only uppercase characters or
 * if a letther(word of one character) is a uppercase character
 */
{
  for(auto letther: word)
    {
      if (charset::ascii_uppercase.find(letther) == string::npos)
        return false;
    }
  return true;
}

// tested - 24 nov 2020
bool isspecial(string word)
/*
 * verify if a word is only of special characters or
 * if a letther(word of one character) is a special character
 */
{

  for(auto letther: word)
    {
      if (charset::special.find(letther) == string::npos)
        return false;
    }
  return true;
}


// tested - 24 nov 2020
Password::Password(string passwd)
  :string(passwd), mask("")
{
  mask = analyzePassword(passwd);
}


// tested - 24 nov 2020
Mask  analyzePassword(string passwd)
/*
 * Analize a string and create a Mask object,
 * also parse the Simple Charset of the password and
 * finally return it.
 */
{
    Mask maskParser;
    // computer the mask of the password and fill the maskStruct
    // #pragma omp parallel for ordered
    //     shared(master_mask, passwd, symbols, passwdStruct)
    for(auto letther: passwd)
    {

            if(islower(letther))
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

    maskStruct mstruct = maskParser.getStruct();
    maskParser.setSCS(scsParser(mstruct));

    return maskParser;

}
