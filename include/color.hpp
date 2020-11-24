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


#ifndef __INCLUDE_STD_RANDOM_H_
#define __INCLUDE_STD_RANDOM_H_
#include <random>
#endif //__INCLUDE_STD_RANDOM_H_


#ifndef __INCLUDE_STD_CTIME_H_
#define __INCLUDE_STD_CTIME_H__
#include <ctime>
#endif //__INCLUDE_STD_CTIME_H_

using namespace std;


namespace color{

  // colors

  string red = "\x1B[31m";
  string green = "\x1B[32m";
  string blue = "\x1B[34m";
  string yellow = "\x1B[93m";

  string end = "\033[0m";

  vector<string> all{red, green, blue, yellow};

  // function to pint text in several color

  string randomText(string text)
  {
    srand(time(0));
    int rdm_idx = rand() % all.size();

    return all[rdm_idx] + text + end;
  }

  string redText(string text)
  {
    return "\x1B[31m" + text + "\033[0m";
  }

  string greenText(string text)
  {
    return "\x1B[32m" + text + "\033[0m";
  }

  string blueText(string text)
  {
    return "\x1B[34m" +  text + "\033[0m";
  }

  string yellowText(string text)
  {
    return "\x1B[93m"  + text + "\033[0m";
  }

}


namespace fine
{

  void print_successful(string msg)
  {
    cout << color::greenText("[+] ") << msg << endl;
  }


  void print_status(string msg)
  {
    cout << color::blueText("[*] ") << msg << endl;
  }

  void print_failure(string msg)
  {
    cout << color::redText("[-] ") << msg << endl;
  }

}

#endif // __COLOR_H__
