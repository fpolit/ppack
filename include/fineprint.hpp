/*
 * Color and fine namespaces definition and implementation
 * color and fine namesapces reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __COLOR_H__
#define __COLOR_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H_


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__


#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H_


#ifndef __INCLUDE_STD_RANDOM_H__
#define __INCLUDE_STD_RANDOM_H__
#include <random>
#endif //__INCLUDE_STD_RANDOM_H__


#ifndef __INCLUDE_STD_CTIME_H_
#define __INCLUDE_STD_CTIME_H__
#include <ctime>
#endif //__INCLUDE_STD_CTIME_H_

using namespace std;

namespace color {
  string red = "\x1B[31m";
  string green = "\x1B[32m";
  string blue = "\x1B[34m";
  string yellow = "\x1B[93m";

  string end = "\033[0m";

  vector<string> all{red, green, blue, yellow};
}

class FinePrint{

  // colors
public:

  // function to pint text in several color
  static string randomColorText(string text)
  {
    
    //srand(time(0));
    int rdm_idx = rand() % color::all.size();

    return color::all[rdm_idx] + text + color::end;
  }

  static string redText(string text)
  {
    return color::red + text + color::end;
  }

  static string greenText(string text)
  {
    return color::green + text + color::end;
  }

  static string blueText(string text)
  {
    return color::blue + text + color::end;
  }

  static string yellowText(string text)
  {
    return color::yellow + text + color::end;
  }


  static void successful(string msg)
  {
    cout << FinePrint::greenText("[+] ") << msg << endl;
  }


  static void status(string msg)
  {
    cout << FinePrint::blueText("[*] ") << msg << endl;
  }

  static void failure(string msg)
  {
    cout << FinePrint::redText("[-] ") << msg << endl;
  }
  static void empty()
  {
      cout << endl;
  }

};

#endif // __COLOR_H__
