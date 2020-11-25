/*
 * @file maskgen.cpp
 * @author glozanoa (gacuna@protonmail.com)
 * @brief Generate mask for brute force that achieve with minimun password complexity requirements.
 * @version 0.1
 * @date 2020-09-27
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

#ifndef __INCLUDE_PROGRAM_OPTIONS_H__
#define __INCLUDE_PROGRAM_OPTIONS_H__
#include<boost/program_options.hpp>
#endif //__INCLUDE_PROGRAM_OPTIONS_H__

using namespace boost;
namespace po = boost::program_options;



// tempprary
#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "../include/pstructs.hpp"
#endif //__INCLUDE_PSTRUCTS_H__

// #ifndef __INCLUDE_PPACK_H__
// #define __INCLUDE_PPACK_H__
// #include "../include/ppack.hpp"
// #endif // __INCLUDE_PPACK_H__

using namespace std;


int main(int argc ,char* argv[])
{
    try
    {

        po::options_description files("Files I/O");
        files.add_options()
            ("output, o", po::value<string>()->default_value("policygen.hcmasks"), "Ouput File.")
          ("input, i", po::value<string>(), "Input File.");

        po::options_description print("Print");
        print.add_options()
            ("show", po::value<bool>()->implicit_value(true)->default_value(false), "Show generated masks.")
            ("quiet, q", po::value<bool>()->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");


        po::options_description mask("Mask Structure");

        // means of -1 value as default value:
        // examples(we use lower as a concrete case, but this can be used equal for other cases[upper, digit and special also length]):
        // minlower = -1; means that the password haven't loweralpha characteres
        // maxlower = -1; means that the maximun number of loweralpha character is undifined
        // (if minlower=3 and (maxlower isn't entered)maxlower=-1 this means that the generated mask can have from 3 to more lower alpha)
        // (if minlower and maxlower isn't entered: then minlower=-1  that means that the password haven't loweralpha charactes even though maxlower=-1)
        // we create this rule to avoid enter unnecesary flags as --maxlower=0 to avoid lower character, instead of that you do not have to enter the flag related to lowers
        // If you forgot enter the flag --minlower but you enter --maxlower=MAXIMUN_LOWERS, then automatically minlower=0 (instead of the default value -1)



        mask.add_options()
            ("minlength", po::value<int>()->default_value(0), "Minimum password length.")
            ("maxlength", po::value<int>()->default_value(0), "Maximum password length.")

            ("minlower", po::value<int>()->default_value(0), "Minimum password lowercase characters.")
            ("maxlength", po::value<int>()->default_value(0), "Maximum password lowercase characters.")

            ("minupper", po::value<int>()->default_value(0), "Minimum password uppercase characters.")
            ("maxupper", po::value<int>()->default_value(0), "Maximum password uppercase characters.")


            ("mindigit", po::value<int>()->default_value(0), "Minimum password digits characters.")
            ("maxdigit", po::value<int>()->default_value(0), "Maximum password digits characters.")

            ("minspecial", po::value<int>()->default_value(0), "Minimum password special characters.")
            ("maxspecial", po::value<int>()->default_value(0), "Maximum password special characters.");

        po::options_description policygen("Generate customized mask for crack passwords");
        policygen.add_options()
            ("version, v", "PPACK version.")
            ("help, h", "Show help.");
        policygen.add(files).add(print).add(mask);

        po::variables_map vm;

        store(po::command_line_parser(argc, argv).
                options(policygen).run(), vm);

        if(vm.count("help")){
            cout << policygen << endl;
            return 1;
        }

        if(vm.count("version"))
        {
          //cout << "PPACK  version " + ppack::VERSION << endl;
            cout << "PPACK  version: 1.0"  << endl;
            return 1;
        }

        if(vm.count("input"))
          {
            // write the support to read from a ini file
          }
        else
          {
            pstruct pargs(vm);

            //PPACK::policygen(pargs);
        return 0;
    }
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
}
