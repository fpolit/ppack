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


// NOTE: Duplicate definition(copy from include/password.hpp)
typedef enum SCS {
  // base types
  loweralpha,
  upperalpha,
  numeric,
  special,

  //common derived combination (unordered)
  alpha,              // (unordered)[loweralpha + upperalpha]

  mixalphaspecial,    // (unordered)[loweralpha + upperalpha + special]
  mixalphanum,        // (unordered)[loweralpha + upperalpha + numeric]
  mixspecialnum,      // (unordered)[special + numeric]
  mixall,             // (unordered)[alpha, numeric, special]
  none                // default value to empty SimpleCharSet variable
}SCS;


bool ismask(string mask);
bool ismasksymbol(string masksymbol); // check if a symbols is a valid symbol mask

class Mask: public std::string
{
private:
  maskStruct mstruct;
  SCS charset;
public:
  Mask():string(){}
  Mask(string mask);
  int length(){return this->size()/2;}
  int complexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
  int masksize(){return this->size()/2;}
  void expand(string masksymbol); // add a mask symbol to a mask
  vector<Mask> permutations();

  friend maskStruct maskAnalysis(Mask mask);
  SCS simpleCharset(){return charset;}
  //  friend SCS simpleCharset(Mask mask);


  // check requirements
  friend bool checkLength(Mask mask, int minlength, int maxlength);
  friend bool checkChartset(Mask mask, vector<SCS> charsets);
  //bool checkAdvanceChartset(vector<ACS> advanceCharsets);
  friend bool checkComplexity(Mask mask, int minCompexity, int maxComplexity);
};

#endif // __MASK_H__
