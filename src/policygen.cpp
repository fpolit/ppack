/**
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

#ifndef __INCLUDE_STD_VECTOR_H_
#define __INCLUDE_STD_VECTOR_H_
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H_


#ifndef __INCLUDE_PROGRAM_OPTIONS_H__
#define __INCLUDE_PROGRAM_OPTIONS_H__
#include<boost/program_options.hpp>
#endif //__INCLUDE_PROGRAM_OPTIONS_H__

//using namespace boost;
namespace po = boost::program_options;


#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../include/ppack.hpp"
#endif // __INCLUDE_PPACK_H__


#ifndef __INCLUDE_LOGOS_H__
#define __INCLUDE_LOGOS_H__
//#include "../include/logos.hpp"
#endif //__INCLUDE_LOGOS_H__

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H__

using namespace std;


int main(int argc ,char* argv[])
{
    try
    {
        //Output File(files)
        string output;
        
        //print parameters(print)
        bool quiet;
        bool show;
    
        //length parameters (password)
        int minlength;
        int maxlength;

        // password complexity requirements (password)                         
        int minlower; 
        int maxlower;                           
        int minupper; 
        int maxupper;                            
        int mindigit;
        int maxdigit;                            
        int minspecial;
        int maxspecial;                       
        

        //parallel parameters (parallel)
        unsigned int threads;      

        po::options_description files("Files I/O");
        files.add_options()
            ("output, o", po::value<string>(&output)->default_value("policygen.hcmasks"), "Ouput File.");

        po::options_description print("Print");
        print.add_options()
            ("show", po::value<bool>(&show)->implicit_value(true)->default_value(false), "Show generated masks.")
            ("quiet, q", po::value<bool>(&quiet)->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");
            
        
        po::options_description password("Password Structure");
        password.add_options()
            ("minlength", po::value<int>(&minlength)->default_value(0), "Minimum password length.")
            ("maxlength", po::value<int>(&maxlength)->default_value(-1), "Maximum password length.")

            ("minlower", po::value<int>(&minlower)->default_value(0), "Minimum password lowercase characters.")
            ("maxlength", po::value<int>(&maxlength)->default_value(-1), "Maximum password lowercase characters.")

            ("minupper", po::value<int>(&minupper)->default_value(0), "Minimum password uppercase characters.")
            ("maxupper", po::value<int>(&maxupper)->default_value(-1), "Maximum password uppercase characters.")

            
            ("mindigit", po::value<int>(&mindigit)->default_value(0), "Minimum password digits characters.")
            ("maxdigit", po::value<int>(&maxdigit)->default_value(-1), "Maximum password digits characters.")

            ("minspecial", po::value<int>(&minspecial)->default_value(0), "Minimum password special characters.")
            ("maxspecial", po::value<int>(&maxspecial)->default_value(-1), "Maximum password special characters.");
                    

         po::options_description parallel("Paralelization");
        parallel.add_options()
            ("threads, t", po::value<unsigned int>(&threads)->default_value(2), "Number of threads.");

        po::options_description policygen("Generate customized mask for crack passwords");
        policygen.add_options()
            ("version, v", "PPACK version.")
            ("help, h", "Show help.");
        policygen.add(files).add(print).add(password).add(parallel);

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
            cout << "PPACK  version 0.1"  << endl;

            return 1;
        }

        if(vm.count("output"))
        {
            output = vm["statsgen"].as<string>();
        }
        else
        {
            show = true;
            output="";
        }

        // NOTE: Finalize implementation of PPACK
        // PPACK ppack();
        // ppack.policygen(output,                         //Output File
        //                 quiet,      show,               //print parameters
        //                 minlength,  maxlength,          //length parameters
        //                 minlower,   maxlower,           //
        //                 minupper,   maxupper,           // password
        //                 mindigit,   maxdigit,           // charset
        //                 minspecial, maxspecial,         //
        //                 threads);                       //parallel parameters)

        return 0;
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
}