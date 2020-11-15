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

#ifndef __INCLUDE_BASEMASK_H__
#define __INCLUDE_BASEMASK_H__
#include "../include/basemask.hpp"
#endif //__INCLUDE_BASEMASK_H__

class PPACK
{
private:
  static string wordlist_file;
  static string output_statsgen;
  static string output_maskgen;
  static string output_policygen;

public:
  PPACK(){};
  //PPACK(string wordlist):wordlist_file{wordlist}{}

    // void statsgen(string output="statsgen.masks",                           //IO parameters
    //             bool hiderare=false, bool quiet=false,                      //print parameters
    //             vector<string> charset={"none"},                            //password charset
    //             int minlength=-1, int maxlength=-1,                         //length parameters
    //             unsigned int threads=2);                                    //parallel parameters

    // void maskgen(string statsgen_output, string output="maskgen.hcmask",    //IO parameters
    //             bool show=true, bool quiet=false,                           //print parameters
    //             vector<Mask> checkmasks={}, string checkmasksfile="",       //checkmask parameters
    //             vector<string> charset={"none"},                            //password charset
    //             int minlength=-1, int maxlength=-1,                         //length parameters
    //             int mincomplexity=1, int maxcomplexity=100,                 //complexity parameters
    //             int minoccurrence=-1, int maxoccurrence=-1,                 //occurrence parameters
    //             unsigned int threads=2);                                    //parallel parameters

    // void policygen(string output="complexity.hcmask",                       //Output File
    //             bool quiet=false, bool show=true,                           //print parameters
    //             int minlength=-1, int maxlength=-1,                         //length parameters
    //             int minlower=-1, int maxlower=-1,                           //
    //             int minupper=-1, int maxupper=-1,                           // password
    //             int mindigit=-1, int maxdigit=-1,                           // charset
    //             int minspecial=-1, int maxspecial=-1,                       //
    //             unsigned int threads=2);                                    //parallel parameters



  static string VERSION = "1.0";
  // this method depend of Base class
  // and corePolicygen is the more important function(this function generate a new Base)
  static void policygen(string output,                       //Output File
                        bool quiet, bool show,                           //print parameters
                        int minlength, int maxlength,                         //length parameters
                        int minlower, int maxlower,                           //
                        int minupper, int maxupper,                           // password
                        int mindigit, int maxdigit,                           // charset
                        int minspecial, int maxspecial);
};



// policygen
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
