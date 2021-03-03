/*
 * Mask class definition
 * Mask class reimplemented 23 nov 2020
 * Mask class with omp support - 30 nov 2020
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
 * Functions with OMP support:
 * bool Mask::ismask(string mask)
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */

#ifndef __MASK_H__
#define __MASK_H__

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__


#ifndef __INCLUDE_STD_MAP_H__
#define __INCLUDE_STD_MAP_H__
#include<map>
#endif // __INCLUDE_STD_MAP_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H__

using namespace std;


// #ifndef __INCLUDE_MASK_EXCEPTIONS_H__
// #define __INCLUDE_MASK_EXCEPTIONS_H__
// #include "../include/mask_exceptions.hpp"
// #endif //__INCLUDE_MASK_EXCEPTIONS_H__

#ifndef __INCLUDE_STD_EXCEPTION_H__
#define __INCLUDE_STD_EXCEPTION_H__
#include <exception>
#endif //__INCLUDE_STD_EXCEPTION_H__

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
  unsigned  int lowercase  = 0;
  unsigned int uppercase  = 0;
  unsigned int special    = 0;
  unsigned int digit      = 0;
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
  string getSymbols(); //get only the symbols of a mask without ? character
  int length(){return this->size()/2;}

  void setComplexity(int complex){complexity = complex;}
  void setACS(ACS asv){advanceCharset = asv;}
  void setSCS(SCS scs){charset = scs;}


  // modificator methods
  friend Mask reallocMask(Mask mask, string maskCharset); // add maskCharset to mask
  void realloc(string maskCharset); // add a mask symbol to a mask and update mstruct
  vector<Mask> permutations();


  // check functions
  static bool ismask(string mask);
  static bool checkLength(Mask mask, int minlength, int maxlength);
  static bool checkSCS(Mask mask, vector<SCS> scs); //check if mask have one of the simple Charset of scs
  static bool checkACS(Mask mask, vector<ACS> acs); //check if mask have one of the advance Charset of acs
  static bool checkComplexity(Mask mask, int minCompexity, int maxComplexity);
  //static bool isMaskCharset(string maskCharset); // check if a symbols is a valid symbol mask


  //  parser functions
  static Mask analysis(string mask);
  //Mask analysis(string mask);
  static SCS scsParser(maskStruct mstruct); // parse a maskStruct and get its SCS
  static ACS acsParser(string mask); // parse a maskStruct and get its ACS
  static string scstoString(SCS simpleCharset); // return the string value of the SCS simpleCharset
  static string acstoString(ACS advanceCharset); // return the string value of the ACS advanceCharset
  static bool equalStruct(Mask kmask, Mask imask); //return true if the maskStruct of the mask are equal otherwise return false 
  static SCS checkSCS(string pscs); //pscs : posible SCS type, if pscs is an invalid SCS, then SCS:none is returned
  static ACS checkACS(string pacs); //pacs : posible ACS type, if pacs is an invalid ACS, then ACS:advnone is returned

  // parse a maskStruct and get the complexity of the mask
  int complexityParser(maskStruct mstruct);
};

/*
 * Mask exceptions
*/
class InvalidMaskcharset : public std::exception
{
  private:
    string maskCharset;
  public:
    InvalidMaskcharset(string invalidMaskCharset);
    const char * what () const throw ();
};



class InvalidMask : public std::exception
{
  private:
    string mask;
  public:
    InvalidMask(string invalidMask);
    const char * what () const throw ();
};

#endif // __MASK_H__
