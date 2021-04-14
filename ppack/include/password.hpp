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

class Password : public std::string
{
private:
  Mask mask;

public:
  Password(string passwd);
  ~Password(){};


  //check functions
  static bool check_length(Password passwd, int minlength, int maxlength);
  static bool check_scs(Password passwd, vector<SCS> pscs); // check if a password have a SCS type in pscs(posibles SCS)
  static bool check_acs(Password passwd, vector<ACS> pacs); // check if a password have a ACS type in pscs(posibles ACS)
  static bool isdigit(string word);
  static bool islower(string word);
  static bool isupper(string word);
  static bool isspecial(string word);

  // get and set methods
  string getv_scs(){return mask.getv_scs();}
  string getv_acs(){return mask.getv_acs();}
  int get_complexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
  SCS get_scs(){return mask.get_scs();}
  ACS get_acs(){return mask.get_acs();}
  string get_mask(){return mask;}

  void set_complexity(int complex){mask.set_complexity(complex);}
  void set_acs(ACS asv){mask.set_acs(asv);}
  void set_scs(SCS scs){mask.set_scs(scs);}

  // parse function
  static Mask analyze_password(string passwd);
};

#endif // _PASSWORD_H
