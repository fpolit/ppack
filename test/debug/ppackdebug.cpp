/*
 * PPACK class depuration of statsgen, maskgen and  policygen methods. 
 * 
 * Depuration: 28 nov 2020
 *
 * Mantainer: glozanoa <glozanoa@uni.pe>
 *
 */


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

using namespace std;


#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../../include/ppack.hpp"
#endif //__INCLUDE_PPACK_H__


int main(int argc, char** argv)
{
    // policygen debug

    // initialization of pstruct to test PPACK.policygen static method
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

    PPACK::policygen(pargs);

    return 0;
}