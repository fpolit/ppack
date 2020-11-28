/*
 * Password class definition
 * Password class reimplemented 23 nov 20202
 *
 * Password class debuged - 24 nov 2020
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __PASSWORD_H__
#define __PASSWORD_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

using namespace std;


#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif // __INCLUDE_MASK_H__


Mask passwdAnalysis(string passwd); //analyze the string passwd and get its mask

class Password : public std::string
{
private:
    Mask mask;

public:
    Password(string passwd);
  ~Password(){};


  // get and set methods
  int getComplexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
  string getValueSCS(){return mask.getValueSCS();}
  string getValueACS(){return mask.getValueACS();}
  SCS getSCS(){return mask.getSCS();}
  ACS getACS(){return mask.getACS();}
  string getMask(){return mask;}

  void setComplexity(int complex){mask.setComplexity(complex);}
  void setACS(ACS asv){mask.setACS(asv);}
  void setSCS(SCS scs){mask.setSCS(scs);}

  //check functions
  static bool checkLength(Password passwd, int minlength, int maxlength);

  

  // / check functions


};

bool isdigit(string letther);
bool islower(string letther);
bool isupper(string letther);
bool isspecial(string letther);

#endif // __PASSWORD_H__
