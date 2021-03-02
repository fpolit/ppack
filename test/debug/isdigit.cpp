#include<iostream>
using namespace std;

#include "omp.h"
// #ifndef __INCLUDE_PASSWORD_H__
// #define __INCLUDE_PASSWORD_H__
// #include "../../include/password.hpp"
// #endif //__INCLUDE_PASSWORD_H__


// character.hpp
namespace charset{

  string ascci_letters =  R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string ascii_lowercase = R"(abcdefghijklmnopqrstuvwxyz)";
  string ascii_uppercase = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ)";
  string digits = R"(0123456789)";
  string special = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
}



// tested - 24 nov 2020
bool isdigit(string word)
/*
 * verify if a word id only of digits or if a letther(word of one character) is a digit
 */
{
  bool isdigitMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!isdigitMaster) continue;

      if (charset::digits.find(word[k]) == string::npos)
        isdigitMaster =  false;
    }

  return isdigitMaster;
}



// tested - 24 nov 2020
bool islower(string word)
/*
 * verify if a word is only lowercase or if a letther(word of one character) is a lowercase
 */
{
  bool islowerMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!islowerMaster) continue;

      if (charset::ascii_lowercase.find(word[k]) == string::npos)
        islowerMaster =  false;
    }

  return islowerMaster;
}

// tested - 24 nov 2020
bool isupper(string word)
/*
 * verify if a word is only uppercase characters or
 * if a letther(word of one character) is a uppercase character
 */
{
  bool isupperMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!isupperMaster) continue;

      if (charset::ascii_uppercase.find(word[k]) == string::npos)
        isupperMaster =  false;
    }

  return isupperMaster;
}

// tested - 24 nov 2020
bool isspecial(string word)
/*
 * verify if a word is only of special characters or
 * if a letther(word of one character) is a special character
 */
{

  bool isspecialMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!isspecialMaster) continue;

      if (charset::special.find(word[k]) == string::npos)
        isspecialMaster =  false;
    }

  return isspecialMaster;
}


int main()
{
  string word = "1434a";
  if(isdigit(word))
    cout << word << " is digit" << endl;
  else
    cout << word << " is not a digit" << endl;

  word = "lilA";
  if(islower(word))
    cout << word << " is lower" << endl;
  else
    cout << word << " is not a lower" << endl;

  word = "LILa";
  if(isupper(word))
    cout << word << " is upper" << endl;
  else
    cout << word << " is not a upper" << endl;


  word = "#$&a";
  if(isspecial(word))
    cout << word << " is special" << endl;
  else
    cout << word << " is not a special" << endl;


  return 0;
}
