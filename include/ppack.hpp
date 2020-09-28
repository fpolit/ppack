#ifndef __PPACK_H__
#define __PPACK_H__

#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H_
#define __INCLUDE_STD_VECTOR_H_
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_
using namespace std;

#ifndef __INCLUDE_MASK_H_
#define __INCLUDE_MASK_H_
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H_

namespace ppack{
string VERSION  = "1.0";
}

class PPACK
{
private:
    string wordlist_file;
    string output_statsgen;
    string output_maskgen;
    string output_policygen;

public:
    PPACK(){}
    PPACK(string wordlist):wordlist_file{wordlist}{}

    void statsgen(string output="statsgen.masks",                           //IO parameters
                bool hiderare=false, bool quiet=false,                      //print parameters
                vector<string> charset={"none"},                            //password charset
                int minlength=-1, int maxlength=-1,                         //length parameters
                unsigned int threads=2);                                    //parallel parameters

    void maskgen(string statsgen_output, string output="maskgen.hcmask",    //IO parameters 
                bool show=true, bool quiet=false,                           //print parameters
                vector<Mask> checkmasks={}, string checkmasksfile="",       //checkmask parameters
                vector<string> charset={"none"},                            //password charset
                int minlength=-1, int maxlength=-1,                         //length parameters
                int mincomplexity=1, int maxcomplexity=100,                 //complexity parameters
                int minoccurrence=-1, int maxoccurrence=-1,                 //occurrence parameters
                unsigned int threads=2);                                    //parallel parameters

    void policygen(string output="complexity.hcmask",                       //Output File
                bool quiet=false, bool show=true,                           //print parameters
                int minlength=-1, int maxlength=-1,                         //length parameters
                int minlower=-1, int maxlower=-1,                           //
                int minupper=-1, int maxupper=-1,                           // password
                int mindigit=-1, int maxdigit=-1,                           // charset
                int minspecial=-1, int maxspecial=-1,                       //
                unsigned int threads=2);                                    //parallel parameters

};


#endif // __PPACK_H__