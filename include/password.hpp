#ifndef __PASSWORD_H__
#define __PASSWORD_H__

#ifndef __INCLUDE_STD_MAP_H_
#define __INCLUDE_STD_MAP_H_
#include<map>
#endif // __INCLUDE_STD_MAP_H_

#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

using namespace std;

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif // __INCLUDE_MASK_H__




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
//more advance combinations (ordered)

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
    none                // default value to empty AdvanceCharSet variable
} ACS;

// Values Simples Character Set
map<SCS, string> SimpleCharSet = {
    {SCS::loweralpha, "loweralpha"},
    {SCS::upperalpha,"upperalpha"},
    {SCS::numeric,"numeric"},
    {SCS::special,"special"},
    {SCS::alpha,"alpha"},
    {SCS::mixalphaspecial,"mixalphaspecial"},
    {SCS::mixalphanum, "mixalphanum"},
    {SCS::mixspecialnum, "mixspecialnum"},
    {SCS::mixall, "mixall"},
    {SCS::none, "none"}
};


map<ACS, string> AdvanceCharSet = {
    {ACS::alphaspecial, "alphaspecial"},
    {ACS::loweralphaspecial, "loweralphaspecial"},
    {ACS::upperalphaspecial, "upperalphaspecial"},
    {ACS::specialalpha, "specialalpha"},
    {ACS::specialloweralpha, "specialloweralpha"},
    {ACS::specialupperalpha, "specialupperalpha"},
    {ACS::alphanum, "alphanum"},
    {ACS::loweralphanum, "loweralphanum"},
    {ACS::upperalphanum, "upperalphanum"},
    {ACS::specialnum, "specialnum"},
    {ACS::numspecial, "numspecial"},
    {ACS::none, "none"}
};


typedef struct PStruct{
        unsigned int lowercase  = 0;
        unsigned int uppercase  = 0;
        unsigned int special    = 0;
        unsigned int digit      = 0;
}PStruct;// Password Structure


class Password : public string
{
private:
    Mask mask;
    int complexity=-1;
    
    // Charater set password
    SCS simple;
    //optional no computer in contructor (default value nane(ACS))
    ACS advance;
    
    PStruct passwdStruct;


public:
    Password(string passwd);
    ~Password(){}

    //string simpleMask(); // remplaced by charset
    string advanceMask(){return mask;}
    // return a type of SCS (map). 
    string scs(); 
    // return a type of ACS (map). 
    string acs();
    int complexity();
    
};
Password::Password(string passwd) 
    :string(passwd)
{
    Mask mask_passwd = analyzePassword(passwd, &passwdStruct, &simple);
    mask = mask_passwd;
    advance = ACS::none;
}

Mask analyzePassword(string passwd, PStruct *pStruct, 
                    SCS* simple);
// determine password's SCS
SCS detSimpleCS(PStruct * pStruct);

#endif // __PASSWORD_H__