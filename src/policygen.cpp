/*
 * policygen - cli interface
 *
 * Depuration - 28 nov 2020
 * policygen (cli interface) depurate.
 *
 * No tested functions: ALL FUNCTION TESTED
 *
 * No implemented functions:
 *  
 * NO COMPLETED
 * --- implement the input of parameters using a input file ---
 *
 * NO COMPLETED
 * --- Implement a beatiful output (call helper function  in corePolicygen) ---
 *
 * NO COMPLETED
 * --- Implement mask writing in a file(call helper function  in corePolicygen) ---
 *
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
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


#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../include/ppack.hpp"
#endif // __INCLUDE_PPACK_H__

using namespace std;

void testBoostOptions(po::variables_map vm)
{

  // Files I/O section
  if(vm.count("output"))
    cout << "output: " << vm["output"].as<string>() << endl;
  else
    cout << "No output option supplied. Default value: " << vm["output"].as<string>() << endl;

  if(vm.count("input"))
    cout << "input: " << vm["input"].as<string>() << endl;
  else
    cout << "No input option supplied. NO Default value."  << endl; //<< vm["input"].as<string>() << endl;

  // Print section
  if(vm.count("show"))
    cout << "show: " << vm["show"].as<bool>() << endl;
  else
    cout << "No show option supplied. Default value: " << vm["show"].as<string>() << endl;

  if(vm.count("quiet"))
    cout << "quiet: " << vm["quiet"].as<bool>() << endl;
  else
    cout << "No quiet option supplied. Default value: " << vm["quiet"].as<string>() << endl;


  // Mask struct section
  if(vm.count("minlength"))
    cout << "minlength: " << vm["minlength"].as<unsigned int>() << endl;
  else
    cout << "No minlength option supplied. Default value: " << vm["minlength"].as<string>() << endl;

  if(vm.count("maxlength"))
    cout << "maxlength: " << vm["maxlength"].as<int>() << endl;
  else
    cout << "No maxlength option supplied. Default value: " << vm["maxlength"].as<string>() << endl;


  if(vm.count("minlower"))
    cout << "minlower: " << vm["minlower"].as<unsigned int>() << endl;
  else
    cout << "No minlower option supplied. Default value: " << vm["minlower"].as<string>() << endl;

  if(vm.count("maxlower"))
    cout << "maxlower: " << vm["maxlower"].as<int>() << endl;
  else
    cout << "No maxlower option supplied. Default value: " << vm["maxlower"].as<string>() << endl;


  if(vm.count("minupper"))
    cout << "minupper: " << vm["minupper"].as<unsigned int>() << endl;
  else
    cout << "No minupper option supplied. Default value: " << vm["minupper"].as<string>() << endl;

  if(vm.count("maxupper"))
    cout << "maxupper: " << vm["maxupper"].as<int>() << endl;
  else
    cout << "No maxupper option supplied. Default value: " << vm["maxupper"].as<string>() << endl;


  if(vm.count("mindigit"))
    cout << "mindigit: " << vm["mindigit"].as<unsigned int>() << endl;
  else
    cout << "No mindigit option supplied. Default value: " << vm["mindigit"].as<string>() << endl;

  if(vm.count("maxdigit"))
    cout << "maxdigit: " << vm["maxdigit"].as<int>() << endl;
  else
    cout << "No maxdigit option supplied. Default value: " << vm["maxdigit"].as<string>() << endl;


  if(vm.count("minspecial"))
    cout << "minspecial: " << vm["minspecial"].as<unsigned int>() << endl;
  else
    cout << "No minspecial option supplied. Default value: " << vm["minspecial"].as<string>() << endl;

  if(vm.count("maxspecial"))
    cout << "maxspecial: " << vm["maxspecial"].as<int>() << endl;
  else
    cout << "No maxspecial option supplied. Default value: " << vm["maxspecial"].as<string>() << endl;
}



int main(int argc ,char* argv[])
{
    try
    {


    po::options_description files("Files I/O");
    files.add_options()
        ("output, o", po::value<string>()->default_value("policygen.hcmasks"), "Ouput File.")
        ("input, i", po::value<string>()->default_value(""), "Input File.");

    po::options_description print("Print");
    print.add_options()
        ("show", po::value<bool>()->implicit_value(true)->default_value(false), "Show generated masks.")
        ("quiet, q", po::value<bool>()->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");


    po::options_description mask("Mask Structure");

    /*
        * MEANS of -1 value as a default value:
        *
        * EXAMPLES:
        * (we use lower as a concrete case, but this can be used equal for other cases[upper, digit and special also length])
        *
        * (if minlower=3 and (maxlower isn't entered)maxlower=-1 this means that the generated mask can have from 3 to more lower alpha)
        *
        * (if minlower and maxlower isn't entered: then minlower=0 and maxlower=0  that means that the password haven't loweralpha charactes), we create this rule to avoid enter unnecesary flags as --maxlower=0 , so instead of that you do not have to enter the flag related to lowers
        *
        *
        *
        * we create this rule to avoid enter unnecesary flags as --maxlower=0 , so instead of that you do not have to enter the flag related to lowers
        */


    mask.add_options()
        ("minlength", po::value<unsigned int>()->default_value(0), "Minimum password length.")
        ("maxlength", po::value<int>()->default_value(0), "Maximum password length.")

        ("minlower", po::value<unsigned int>()->default_value(0), "Minimum password lowercase characters.")
        ("maxlower", po::value<int>()->default_value(0), "Maximum password lowercase characters.")

        ("minupper", po::value<unsigned int>()->default_value(0), "Minimum password uppercase characters.")
        ("maxupper", po::value<int>()->default_value(0), "Maximum password uppercase characters.")


        ("mindigit", po::value<unsigned int>()->default_value(0), "Minimum password digits characters.")
        ("maxdigit", po::value<int>()->default_value(0), "Maximum password digits characters.")

        ("minspecial", po::value<unsigned int>()->default_value(0), "Minimum password special characters.")
        ("maxspecial", po::value<int>()->default_value(0), "Maximum password special characters.");

    po::options_description policygen("Generate customized mask for crack passwords");
    policygen.add_options()
        ("version, v", "PPACK version.")
        ("help, h", "Show help.");
    policygen.add(files).add(print).add(mask);

    po::variables_map vm;

    po::store(po::command_line_parser(argc, argv).
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

    // cout << "--- vm(before parsing arguments) ---" << endl;
    // testBoostOptions(vm);

    cout << "--- vm(after parsing arguments) ---" << endl;
    pstruct pargs(vm);
    pargs.debug();  


    PPACK::policygen(pargs);

        return 0;
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
}
