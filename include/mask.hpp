#ifndef __MASK_H__
#define __MASK_H__

#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H_
#define __INCLUDE_STD_VECTOR_H_
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H_

using namespace std;

typedef struct maskSymbols
{
    vector<string> mask_symbols{"?l", "?u", "?d", "?s", "?a"};
    string lowercase    = "?l";
    string uppercase    = "?u";
    string special      = "?s";
    string digit        = "?d";
    string all          = "?a";

}maskSymbols;

typedef struct letterMask
{
    string lowercase    = "l";
    string uppercase    = "u";
    string special      = "s";
    string digit        = "d";
    string all          = "a";
}LetterMask;

bool ismask(string mask);

class Mask: public string
{
public:
    Mask():string(){}
    Mask(string mask);
    size_t size() const; 
};


Mask::Mask(string mask) 
{
   //verify that mask have the format of a MASK
    if(ismask(mask)){
        string(mask); 
    }
    else{
        throw "Invalid mask: " + mask;
    }
}


#endif // __MASK_H__