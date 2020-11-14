#ifndef __MASK_H__
#define __MASK_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H__

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


typedef struct maskStruct
{
   int lowercase  = 0;
   int uppercase  = 0;
   int special    = 0;
   int digit      = 0;
}maskStruct;


bool ismask(string mask);
bool ismasksymbol(string masksymbol); // check if a symbols is a valid symbol mask

class Mask: public std::string
{
private:
  maskStruct mstruct;

public:
  Mask():string(){}
  Mask(string mask);
  int masksize(){return this->size()/2;}
  void expand(string masksymbol); // add a mask symbol to a mask
  vector<Mask> permutations();

  friend maskStruct maskAnalysis(Mask mask);
};

#endif // __MASK_H__
