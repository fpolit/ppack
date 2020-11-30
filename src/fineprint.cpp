#ifndef __INCLUDE_FINEPRINT_H__
#define __INCLUDE_FINEPRINT_H__
#include "../include/fineprint.hpp"
#endif //__INCLUDE_FINEPRINT_H_


namespace color {
  string red = "\x1B[31m";
  string green = "\x1B[32m";
  string blue = "\x1B[34m";
  string yellow = "\x1B[93m";

  string end = "\033[0m";

  vector<string> all{red, green, blue, yellow};
}  
  
string FinePrint::randomColorText(string text)
{

//srand(time(0));
int rdm_idx = rand() % color::all.size();

return color::all[rdm_idx] + text + color::end;
}

string FinePrint::redText(string text)
{
return color::red + text + color::end;
}

string FinePrint::greenText(string text)
{
return color::green + text + color::end;
}

string FinePrint::blueText(string text)
{
return color::blue + text + color::end;
}

string FinePrint::yellowText(string text)
{
return color::yellow + text + color::end;
}


void FinePrint::successful(string msg)
{
cout << FinePrint::greenText("[+] ") << msg << endl;
}


void FinePrint::status(string msg)
{
cout << FinePrint::blueText("[*] ") << msg << endl;
}

void FinePrint::failure(string msg)
{
cout << FinePrint::redText("[-] ") << msg << endl;
}
void FinePrint::empty()
{
    cout << endl;
}