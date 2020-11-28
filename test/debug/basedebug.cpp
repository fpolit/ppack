/*
 * Base class depuration - 27 nov 2020
 *
 * Depuration: 27 nov 2020
 *  
 *
 * No tested functions: 
 *
 * No implemented functions: 
 *
 * Mantainer: glozanoa <glozanoa@uni.pe>
 *
 */

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include <string>
#endif //__INCLUDE_STD_STRING_H__

using namespace std;

#ifndef __INCLUDE_PSTRUCT_H__
#define __INCLUDE_PSTRUCT_H__
#include "../../include/basepoli.hpp"
#endif //__INCLUDE_PSTRUCT_H__

int main(int argc, char **argv)
{

    // initialization of pstruct to test base Class
    unsigned int min_length = 5;
    int max_length = 7;

    unsigned int min_lower = 2;
    int max_lower = -1;

    unsigned int min_upper = 0;
    int max_upper = 0;

    unsigned int min_digit = 0;
    int max_digit = 0;

    unsigned int min_special = 1;
    int max_special = 2;

    bool quiet_print = true;
    bool show_masks = false;

    string output_file = "";
    string input_file = "";

    pstruct pargs(min_length, max_length,    //
                    min_lower, max_lower,      // masks
                    min_upper, max_upper,      // struct
                    min_digit, max_digit,      // parameters
                    min_special, max_special,  // 
                    quiet_print, show_masks,          // print parameters
                    output_file, input_file);

    //Base base(pargs);

    vector<Base*> aa = corePolicygen(pargs);
    //vector<Base> aa = corePolicygen(pargs);
    cout << "output corePolicygen: " << endl;
    // for(auto base: aa)
    // {
    //     base.showMasks();
    // }


    // for(int k =0; k<aa.size(); k++)
    //     delete aa[k];


    cout << "(main)I get it!" << endl;

    return 0;
}