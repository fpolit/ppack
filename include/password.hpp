/*
 * Password class definition
 * Password class reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __PASSWORD_H__
#define __PASSWORD_H__

#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

using namespace std;


#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif // __INCLUDE_MASK_H__


Mask passwdAnalysis(string passwd); //analyze the string passwd and get its mask

class Password : public string
{
private:
    Mask mask;

public:
    Password(string passwd);
  ~Password(){};


  // get and set methods
  int getComplexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
  SCS getSCS(){return mask.getSCS();}
  ACS getACS(){return mask.getACS();}

  void setComplexity(int complex){mask.setComplexity(complex);}
  void setACS(ACS asv){mask.setACS(asv);}
  void setSCS(SCS scs){mask.setSCS(scs);}

  string getMask(){return mask;}
};
#endif // __PASSWORD_H__
