/*
 * Mask class definition
 * Mask class reimplemented 23 nov 20202
 *
 *
 * Depuration:
 * Mask class tested 24 nov 2020.
 *
 *
 * No tested functions:
 * bool Mask::checkSCS(Mask mask, vector<SCS> scs); //check if mask have one of the simple Charset of scs
 * bool Mask::checkACS(Mask mask, vector<ACS> acs); //check if mask have one of the advance Charset of acs
 *
 * No implemented functions:
 * vector<Mask> Mask::permutations();
 *
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */

#ifndef __MASK_H__
#define __MASK_H__


#ifndef __INCLUDE_STD_MAP_H_
#define __INCLUDE_STD_MAP_H_
#include<map>
#endif // __INCLUDE_STD_MAP_H_

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H__

using namespace std;



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

typedef enum ACS{
//more advance charste (ordered combinations)

    //combination of alpha(lower, upper) + special
    alphaspecial,       // [(unordered)(loweralpha + upperalpha)] + special
    loweralphaspecial,  // loweralpha + special
    upperalphaspecial,  // upperalpha + special

    specialalpha,       // special + [(unordered)(loweralpha + upperalpha)]
    specialloweralpha,  // special + loweralpha
    specialupperalpha,  // special + upperalpha

    // combination of alpha(lower, upper) + numeric

    alphanum,           // [(unordered)(loweralpha + upperalpha)] + numeric
    loweralphanum,      // loweralpha + numeric
    upperalphanum,      // upperalpha + numeric

    // combination of special + numeric

    specialnum,         // special + numeric
    numspecial,         // numeric + special
    advnone                // default value to empty AdvanceCharSet variable
} ACS;

typedef struct maskStruct
{
  int lowercase  = 0;
  int uppercase  = 0;
  int special    = 0;
  int digit      = 0;
}maskStruct;


class Mask: public std::string
{
private:
  maskStruct mstruct;
  SCS charset;

  ACS advanceCharset;
  int complexity;

public:
  Mask();
  Mask(string mask);

  // get and set methods
  int getComplexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
  SCS getSCS(){return charset;}
  ACS getACS();
  string getValueSCS();
  string getValueACS();
  maskStruct getStruct(){return mstruct;}
  int length(){return this->size()/2;}

  void setComplexity(int complex){complexity = complex;}
  void setACS(ACS asv){advanceCharset = asv;}
  void setSCS(SCS scs){charset = scs;}


  // modificator methods
  void realloc(string maskCharset); // add a mask symbol to a mask and update mstruct
  vector<Mask> permutations();

  //  parser friend functions
  static Mask analysis(string mask);
};



// check functions
bool ismask(string mask);
bool checkLength(Mask mask, int minlength, int maxlength);
bool checkSCS(Mask mask, vector<SCS> scs); //check if mask have one of the simple Charset of scs
bool checkACS(Mask mask, vector<ACS> acs); //check if mask have one of the advance Charset of acs
bool checkComplexity(Mask mask, int minCompexity, int maxComplexity);
//static bool isMaskCharset(string maskCharset); // check if a symbols is a valid symbol mask


//  parser friend functions
//Mask analysis(string mask);
SCS scsParser(maskStruct mstruct); // parse a maskStruct and get its SCS

#endif // __MASK_H__
