/*
 * Password class depuration
 * Date: 24 nov 2020
 *
 * Mantainer: glozanoa <glozanoa@uni.pe>
 *
 */


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

using namespace std;


#ifndef __INCLUDE_PASSWORD_H__
#define __INCLUDE_PASSWORD_H__
#include "../../include/password.hpp"
#endif //__INCLUDE_PASSWORD_H__



int main(int argc, char** argv)
{

  /*
   * Test of function isSOMEGTHING(letther)
   *
   * RESULT: isSOMETHING function work fine with string of length 1
   * but ACCEPT string og length greather than 1 (SOLVE IT)
   *
   */
  // string letther = "?";
  // cout << "islower(" << letther << "): " << islower(letther) << endl;
  // cout << "isupper(" << letther << "): " << isupper(letther) << endl;
  // cout << "isdigit(" << letther << "): " << isdigit(letther) << endl;
  // cout << "isspecial(" << letther << "): " << isspecial(letther) << endl;


  /*
   * ---- Test case ---
   * password :  leP$74?#Bye
   * mascara  :  ?l?l?u?s?d?d?s?s?u?l?l
   * acs      :  mixall
   */

  string spasswd = "leP$74?#Bye";
  //string spasswd = "leP$?#Bye";
  Password passwd(spasswd);

  cout << "private attributes Password(" << passwd << ")" << endl;
  cout << "mask: " << passwd.getMask() << endl;

  cout << "\nget and set methods" << endl;
  cout << "scs: " << passwd.getSCS() << endl;

  return 0;
}
