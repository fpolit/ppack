#ifndef __PPACK_H__
#define __PPACK_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_

using namespace std;

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H__


#ifndef __INCLUDE_PASSWORD_H__
#define __INCLUDE_PASSWORD_H__
#include "password.hpp"
#endif //__INCLUDE_PASSWORD_H__

// #ifndef __INCLUDE_BASEMASK_H__
// #define __INCLUDE_BASEMASK_H__
// #include "../include/basemask.hpp"
// #endif //__INCLUDE_BASEMASK_H__

string PPACK_VERSION = "1.0";

class PPACK
{
private:
  static string wordlist_file;
  static string output_statsgen;
  static string output_maskgen;
  static string output_policygen;

public:

  PPACK(){}
  // PPACK(){VERSION = "1.0";}
  //PPACK(string wordlist):wordlist_file{wordlist}{}

  void statsgen(string wordlist, string output,                           //IO parameters
                bool hiderare, bool quiet,                      //print parameters
                vector<string> charset,                            //password charset
                  int minlength, int maxlength);                         //length parameters


    void maskgen(string statsgen_output, string output,    //IO parameters
                bool show, bool quiet,                           //print parameters
                 vector<Mask> checkmasks,string checkmasksfile,       //checkmask parameters
                vector<string> charset,                            //password charset
                int minlength, int maxlength,                         //length parameters
                int mincomplexity, int maxcomplexity,                 //complexity parameters
                 int minoccurrence, int maxoccurrence);                 //occurrence parameters




  // this method depend of Base class
  // and corePolicygen is the more important function(this function generate a new Base)
  static void policygen(string statsgen_output, string output,                       //Output File
                        bool quiet, bool show,                           //print parameters
                        int minlength, int maxlength,                         //length parameters
                        int minlower, int maxlower,                           //
                        int minupper, int maxupper,                           // password
                        int mindigit, int maxdigit,                           // charset
                        int minspecial, int maxspecial);
};


///////////////////////////////////////////////////////////////////////////
///////////////////////// statgen   ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


typedef struct statstruct
{
  map<SCS, int> scs;
  map<Mask, int> mask;
  map<unsigned int, int> length;
}statstruct;


///////////////////////////////////////////////////////////////////////////
///////////////////////// maskgen   ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


typedef struct maskgenStruct
{
  int minlength; int maxlength;
  int mincompexity; int maxcomplexity;
  int minoccurence; int maxoccurence;
  vector<string> charsets;
}maskgenStruct;

maskgenStruct init_maskgen_struct(int minlength, int maxlength,
                         int mincompexity, int maxcomplexity,
                         int minoccurence, int maxoccurence,
                         vector<string> charsets)
{
  maskgenStruct mskgn;

  mskgn.minlength = minlength;
  mskgn.maxlength = maxlength;
  mskgn.mincompexity = mincompexity;
  mskgn.maxcomplexity = maxcomplexity;
  mskgn.minoccurence = minoccurence;
  mskgn.maxoccurence = maxoccurence;
  mskgn.charsets = charsets;

  return mskgn;
}





///////////////////////////////////////////////////////////////////////////
///////////////////////// policygen ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// requirements for the creation of masks
typedef struct poliStruct
{
  int minlength; int maxlength;                         //length parameters
  int minlower; int maxlower;                           //
  int minupper; int maxupper;                           // password
  int mindigit; int maxdigit;                           // charset
  int minspecial; int maxspecial;
}poliStruct;

// base class of policygen
class Base
{
private:
  poliStruct bstruct; // base struct , entered options for policygen
  vector<Mask> *base;
  unsigned int length;

public:

  Base(poliStruct init);
  void maskStep(); // generate all the posible mask of length = length +1(step)

  void appendMask(Mask step); // next step mask

  unsigned int getLength(){return length;}
  int numberMasks(){return base->size();}


  int getPoliMinLength(){return bstruct.minlength;}
  int getPoliMaxLength(){return bstruct.maxlength;}

  ~Base();
};




poliStruct init_polistruct(int minlength, int maxlength,                         //length parameters
                           int minlower, int maxlower,                           //
                           int minupper, int maxupper,                           // password
                           int mindigit, int maxdigit,                           // charset
                           int minspecial, int maxspecial);


void corePolicygen();

#endif // __PPACK_H__
