#ifndef __CHARACTER_H__
#define __CHARACTER_H__


#ifndef __INCLUDE_STD_STRING_H_
#define __INCLUDE_STD_STRING_H_
#include<string>
#endif //__INCLUDE_STD_STRING_H_

using namespace std;

typedef struct Character
{
    string ascci_letters =  R"(abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ)";
    string ascii_lowercase = R"(abcdefghijklmnopqrstuvwxyz)";
    string ascii_uppercase = R"(ABCDEFGHIJKLMNOPQRSTUVWXYZ)";
    string digits = R"(0123456789)";
    string special = R"(!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)";
    string printable = R"(0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c)";
    string whitespace = R"( \t\n\r\x0b\x0c)";
    string masksymbols = R"(ludsa)";
}Character;

bool islower(string letther);
bool isupper(string letther);
bool isdigit(string letther);
bool isspecial(string letther);

#endif // __CHARACTER_H__