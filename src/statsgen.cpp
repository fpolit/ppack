/*
 * statsgen - cli interface
 *
 *
 * Depuration - 28 nov 2020
 *  statsgen (cli interface) depurate.
 *
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
 * Maintainer: glozanoa <glozanoa@uni.pe>
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
#include "../include/ppack.hpp"
#endif // __INCLUDE_PPACK_H__


// #ifndef __INCLUDE_LOGOS_H__
// #define __INCLUDE_LOGOS_H__
// #include "../include/logos.hpp"
// #endif //__INCLUDE_LOGOS_H__

#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "../include/pstructs.hpp"
#endif //__INCLUDE_PSTRUCTS_H__

#ifndef __INCLUDE_PROGRAM_OPTIONS_H__
#define __INCLUDE_PROGRAM_OPTIONS_H__
#include<boost/program_options.hpp>
#endif //__INCLUDE_PROGRAM_OPTIONS_H__

//using namespace boost;
namespace po = boost::program_options;

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
    cout << "No input option supplied. Default value: "  << vm["input"].as<string>() << endl;

  // Print section
  if(vm.count("hiderare"))
    cout << "hiderare: " << vm["hiderare"].as<bool>() << endl;
  else
    cout << "No hiderare option supplied. Default value: " << vm["hiderare"].as<string>() << endl;

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
}

int main(int argc ,char* argv[])
{
  try
  {
    po::options_description files("Files I/O");
    files.add_options()
        ("wordlist, w", po::value<string>(), "Wordlist.")
        ("output, o", po::value<string>()->default_value("statsgen.masks"), "Ouput File.")
      ("input, i", po::value<string>()->default_value(""), "Input File.");


    po::options_description password("Password Structure");
    password.add_options()
        ("charset, c", po::value<vector<string>>(), "Password's charset.")
        ("minlength", po::value<unsigned int>()->default_value(0), "Minimum password length.")
        // if no length option entered minlength=0 and maxlength=-1 (without eny filter of length)
        ("maxlength", po::value<int>()->default_value(-1), "Miximum password length.");

    po::options_description print("Print");
    print.add_options()
        ("hiderare", po::value<bool>()->implicit_value(true)->default_value(false), "Omit items with occurrence of less than 1%.")
        ("quiet, q", po::value<bool>()->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");

    po::options_description statsgen("Generate statistic of a wordlists that help you crack passwords");
    statsgen.add_options()
        ("version, v", "PPACK version.")
        ("help, h", "Show help.");
    statsgen.add(files).add(password).add(print);

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

    // if(vm.count("input"))
    //   {
    //     // write the support to read from a ini file
    //   }
    //cout << "--- vm(before parsing arguments) ---" << endl;
    //testBoostOptions(vm);

    cout << "--- vm(parsing arguments) ---" << endl;
    sstruct pargs(vm);
    pargs.debug();  


    PPACK::statsgen(pargs);
    
  }
  catch(std::exception& e)
  {
    cout << e.what() << endl;
    return 1;
  }
  return 0;
}
