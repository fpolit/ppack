/*
 * Password class definition
 * Password class reimplemented 23 nov 20202
 * Password class with omp support - 30 nov 2020
 *
 * Password class debuged - 24 nov 2020
 *
 *
 *
 * Functions with OMP support:
 * static bool isdigit(string word);
 * static bool islower(string word);
 * static bool isupper(string word);
 * static bool isspecial(string word);
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef _PASSWORD_H
#define _PASSWORD_H

#include<string>

using namespace std;

#include "mask.hpp"


//Mask passwdAnalysis(string passwd); //analyze the string passwd and get its mask
namespace ppack
{
  class Password : public std::string
  {
  private:
    Mask mask;

  public:
    Password(string passwd);
    ~Password(){};


    // get and set methods
    int get_complexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
    string getv_scs(){return mask.getValueSCS();}
    string getv_acs(){return mask.getValueACS();}
    SCS scs(){return mask.getSCS();}
    ACS acs(){return mask.getACS();}
    string mask(){return mask;}

    void set_complexity(int complex){mask.setComplexity(complex);}
    void set_acs(ACS asv){mask.setACS(asv);}
    void set_scs(SCS scs){mask.setSCS(scs);}

    // parse function
    //static Mask  analyzePassword(string passwd);


    //check functions
    static bool check_length(Password passwd, int minlength, int maxlength);
    static bool check_scs(Password passwd, vector<SCS> pscs); // check if a password have a SCS type in pscs(posibles SCS)
    static bool check_acs(Password passwd, vector<ACS> pacs); // check if a password have a ACS type in pscs(posibles ACS)


    static bool isdigit(string word);
    static bool islower(string word);
    static bool isupper(string word);
    static bool isspecial(string word);
  };
}


#endif // _PASSWORD_H
