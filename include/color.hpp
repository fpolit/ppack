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
#include<cstdlib>
#include<ctime>
#endif // __INCLUDE_STD_RANDOM_H__



using namespace std;

typedef struct ascii_colors
{
  string red = "\x1B[31m";
  string green = "\x1B[32m";
  string blue = "\x1B[34m";
  string yellow = "\x1B[93m";

  string end = "\033[0m";

  vector<string> all{red, green, blue, yellow};
}ascii_color;



class Color
{
public:
  Color(){}
  static string redText(string text);
  static string greenText(string text);
  static string blueText(string text);
  static string yellowText(string text);
  static string randomText(string text); //
};

string Color::randomText(string text)
{
  ascii_color colors;
  srand(time(0));
  int rdm_idx = rand() % colors.all.size();

  return colors.all[rdm_idx] + text + colors.end;
}

string Color::redText(string text)
{
  return "\x1B[31m" + text + "\033[0m";
}

string Color::greenText(string text)
{
  return "\x1B[32m" + text + "\033[0m";
}

string Color::blueText(string text)
{
  return "\x1B[34m" +  text + "\033[0m";
}

string Color::yellowText(string text)
{
  return "\x1B[93m"  + text + "\033[0m";
}


void print_successful(string msg)
{
  cout << Color::greenText("[+] ") << msg << endl;
}


void print_status(string msg)
{
  cout << Color::blueText("[*] ") << msg << endl;
}

void print_failure(string msg)
{
  cout << Color::redText("[-] ") << msg << endl;
}


#endif // __COLOR_H__
