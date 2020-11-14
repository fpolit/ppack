#ifndef __INCLUDE_CHARACTER_H__
#define __INCLUDE_CHARACTER_H__
#include "../include/character.hpp"
#endif //__INCLUDE_CHARACTER_H__


Character characters;

bool isdigit(string letther) 
{
    string digits = characters.digits;
    if (digits.find(letther) == string::npos)
    {
        return false;
    }
    return true;
}

bool islower(string letther) 
{
    string lowercase = characters.ascii_lowercase;
    if (lowercase.find(letther) == string::npos)
    {
        return false;
    }
    return true;
}

bool isupper(string letther) 
{
    string uppercase = characters.ascii_uppercase;
    if (uppercase.find(letther) == string::npos)
    {
        return false;
    }
    return true;
}

bool isspecial(string letther) 
{
    string special = characters.special;
    if (special.find(letther) == string::npos)
    {
        return false;
    }
    return true;
}
