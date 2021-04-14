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

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "charset.hpp"
#include "exceptions/mask.hpp"

using namespace std;

#ifndef _MASK_H
#define _MASK_H

typedef struct maskStruct
{
  unsigned int lowercase  = 0;
  unsigned int uppercase  = 0;
  unsigned int special    = 0;
  unsigned int digit      = 0;
}maskStruct;


class Mask: public std::string
{
  //static Mask NONE = Mask();

private:
  maskStruct mstruct;
  SCS charset;

  ACS adv_charset;
  int complexity;

public:
  Mask();
  Mask(string mask);

  // get and set methods
  int get_complexity(){return 0;} // NOTA: IMPLEMENTAR LA COMPLEJIDAD DE UNA MASCARA
  SCS get_scs(){return charset;}
  ACS get_acs(){return adv_charset;}
  string getv_scs(){return scs_map[charset];}
  string getv_acs(){return acs_map[adv_charset];}
  maskStruct get_mask_struct(){return mstruct;}
  string symbols(); //get only the symbols of a mask without ? character
  int length(){return this->size()/2;}

  void set_complexity(int complex){complexity = complex;}
  void set_scs(SCS scs){charset = scs;}
  void set_acs(ACS acs){adv_charset = acs;}


  // modificator methods
  void realloc(string mask_charset); // add a mask symbol to a mask and update mstruct
  friend Mask realloc_mask(Mask mask, string mask_charset); // add maskCharset to mask
  //vector<Mask> permutations(); // NOT IMPLEMENTED


  // check functions
  static bool ismask(string mask);
  static bool check_length(Mask mask, int minlength, int maxlength);
  static bool check_scs(Mask mask, vector<SCS> scs); //check if mask have one of the simple Charset of scs
  static bool check_acs(Mask mask, vector<ACS> acs); //check if mask have one of the advance Charset of acs
  static bool check_complexity(Mask mask, int minCompexity, int maxComplexity);
  static bool is_mask_charset(string maskCharset);
  //static bool isMaskCharset(string maskCharset); // check if a symbols is a valid symbol mask


  //  parser functions
  static Mask analysis(string mask);
  //Mask analysis(string mask);
  static SCS scs_parser(maskStruct mstruct); // parse a maskStruct and get its SCS
  static ACS acs_parser(string mask); // parse a maskStruct and get its ACS
  static string scs2string(SCS simpleCharset); // return the string value of the SCS simpleCharset
  static string acs2string(ACS advanceCharset); // return the string value of the ACS advanceCharset
  static bool equal_struct(Mask kmask, Mask imask); //return true if the maskStruct of the mask are equal otherwise return false
  static SCS check_scs(string pscs); //pscs : posible SCS type, if pscs is an invalid SCS, then SCS:none is returned
  static ACS check_acs(string pacs); //pacs : posible ACS type, if pacs is an invalid ACS, then ACS:advnone is returned

  // parse a maskStruct and get the mask complexity
  //int complexity_parser(maskStruct mstruct);

  // operators
  string operator[](int index);
  bool operator==(const Mask other);
  Mask split(int index);
};

Mask NONE_MASK = Mask();

#endif // _MASK_H
