/*
 * Color and fine namespaces definition and implementation
 * color and fine namesapces reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __FINEPRINT_H__
#define __FINEPRINT_H__

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



class FinePrint
{
public:
  // function to pint text in several color
  static string randomColorText(string text);
  static string redText(string text);
  static string greenText(string text);
  static string blueText(string text);
  static string yellowText(string text);

  static void successful(string msg);
  static void status(string msg);
  static void failure(string msg);
  static void empty();
};

#endif // __FINEPRINT_H__
