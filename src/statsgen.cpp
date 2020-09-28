/**
 * @file statsgen.cpp
 * @author glozanoa (gacuna@protonmail.com)
 * @brief Generate statistic of a wordlists that help you crack passwords.
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

#ifndef __INCLUDE_STD_VECTOR_H_
#define __INCLUDE_STD_VECTOR_H_
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H_


#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
//#include "../include/ppack.hpp"
#endif // __INCLUDE_PPACK_H__


#ifndef __INCLUDE_LOGOS_H__
#define __INCLUDE_LOGOS_H__
//#include "../include/logos.hpp"
#endif //__INCLUDE_LOGOS_H__


#ifndef __INCLUDE_PROGRAM_OPTIONS_H__
#define __INCLUDE_PROGRAM_OPTIONS_H__
#include<boost/program_options.hpp>
#endif //__INCLUDE_PROGRAM_OPTIONS_H__

//using namespace boost;
namespace po = boost::program_options;

using namespace std;


int main(int argc ,char* argv[])
{
    try
    {
        //IO parameters
        string wordlist;
        string output;

        //print parameters
        bool hiderare;
        bool quiet;

        //password properties
        vector<string> charset;

        //length parameters
        int minlength;
        int maxlength;
        
        unsigned int threads;

        po::options_description files("Files I/O");
        files.add_options()
            ("wordlist, w", po::value<string>(), "Wordlist.")
            ("output, o", po::value<string>(&output)->default_value("statsgen.masks"), "Ouput File.");

        po::options_description password("Password Structure");
        password.add_options()
            ("charset, c", po::value<vector<string>>(), "Password's charset.")
            ("minlength", po::value<int>(&minlength)->default_value(-1)->implicit_value(-1), "Minimum password length.")
            ("maxlength", po::value<int>(&maxlength)->default_value(-1)->implicit_value(-1), "Miximum password length.");        

        po::options_description print("Print");
        print.add_options()
            ("hiderare", po::value<bool>(&hiderare)->implicit_value(true)->default_value(false), "Omit items with occurrence of less than 1%.")
            ("quiet, q", po::value<bool>(&quiet)->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");

        po::options_description parallel("Paralelization");
        parallel.add_options()
            ("threads, t", po::value<unsigned int>(&threads)->default_value(2), "Number of threads.");

        po::options_description statsgen("Generate statistic of a wordlists that help you crack passwords");
        statsgen.add_options()
            ("version, v", "PPACK version.")
            ("help, h", "Show help.");
        statsgen.add(files).add(password).add(print).add(parallel);

        po::variables_map vm;

        store(po::command_line_parser(argc, argv).
                options(statsgen).run(), vm);

        if(vm.count("help")){
            cout << statsgen << endl;
            return 1;
        }

        if(vm.count("version"))
        {
            //cout << "PPACK  version " + ppack::VERSION << endl;
            cout << "PPACK  version 0.1"  << endl;

            return 1;
        }

        if(vm.count("wordlist"))
        {
            wordlist = vm["wordlist"].as<string>();
            cout << "HELLO" << endl;
            // Finalize implementation of classes
            //PPACK ppack(wordlist);
            //ppack.statsgen(output, hiderare, quiet, charset, minlength, maxlength, threads);
        }
        else
        {
            cout << "No wordlist file supplied." << endl;
            cout << statsgen << endl;
            return 1;
        }
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}