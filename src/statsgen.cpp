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



typedef struct statsargi{
  string *wordlist;
  string *output; string *input;                       //Output File
  bool *quiet; //bool *show;                           //print parameters
  int *minlength; int *maxlength;                         //length parameters
  // int *minlower; int *maxlower;                           //
  // int *minupper; int *maxupper;                           // password
  // int *mindigit; int *maxdigit;                           // charset
  // int *minspecial; int *maxspecial;
}statsargi;


void validate_arguments(po::variables_map vm, statsargi *statargs)
/*
 * Validate the process of flag reading and set default value to forgeted parameters
 * also assign these validated parameters to their varibles
 */
{
  //Output File parameter(files section)
  if(vm.count("output"))
    {
      *(statargs->output) = vm["output"].as<string>();
    }

  //print parameters(print section)
  if(vm.count("quiet"))
    {
      *(statargs->quiet) = vm["quiet"].as<bool>();
    }

  // if(vm.count("show"))
  //   {
  //     *(statargs->show) = vm["show"].as<bool>();
  //   }

  //length parameters (mask section)
  if(vm.count("minlength") && vm.count("maxlength"))
    {
      *(statargs->minlength) = vm["minlength"].as<int>();
      *(statargs->maxlength) = vm["maxlength"].as<int>();
    }
  else if(vm.count("maxlength"))
    {
      *(statargs->maxlength) = vm["maxlength"].as<int>();
      *(statargs->minlength) = 0;
    }
  else
    {
      *(statargs->minlength) = vm["minlength"].as<int>();
      *(statargs->maxlength) = vm["maxlength"].as<int>(); //set maxlength to the default value -1
    }

  // password complexity requirements (mask section)

  // // lower characters
  // if(vm.count("minlower") && vm.count("maxlower"))
  //   {
  //     *(polyargs->minlower) = vm["minlower"].as<int>();
  //     *(polyargs->maxlower) = vm["maxlower"].as<int>();
  //   }
  // else if(vm.count("maxlower"))
  //   {
  //     *(polyargs->maxlower) = vm["maxlower"].as<int>();
  //     *(polyargs->minlower) = 0;
  //   }
  // else
  //   {
  //     *(polyargs->minlower) = vm["minlower"].as<int>();
  //     *(polyargs->maxlower) = vm["maxlower"].as<int>(); //set maxlower to the default value -1
  //   }

  // // upper characters
  // if(vm.count("minupper") && vm.count("maxupper"))
  //   {
  //     *(polyargs->minupper) = vm["minupper"].as<int>();
  //     *(polyargs->maxupper) = vm["maxupper"].as<int>();
  //   }
  // else if(vm.count("maxupper"))
  //   {
  //     *(polyargs->maxupper) = vm["maxupper"].as<int>();
  //     *(polyargs->minupper) = 0;
  //   }
  // else
  //   {
  //     *(polyargs->minupper) = vm["minupper"].as<int>();
  //     *(polyargs->maxupper) = vm["maxupper"].as<int>(); //set maxupper to the default value -1
  //   }

  // // digit characters
  // if(vm.count("mindigit") && vm.count("maxdigit"))
  //   {
  //     *(polyargs->mindigit) = vm["mindigit"].as<int>();
  //     *(polyargs->maxdigit) = vm["maxdigit"].as<int>();
  //   }
  // else if(vm.count("maxdigit"))
  //   {
  //     *(polyargs->maxdigit) = vm["maxdigit"].as<int>();
  //     *(polyargs->mindigit) = 0;
  //   }
  // else
  //   {
  //     *(polyargs->mindigit) = vm["mindigit"].as<int>();
  //     *(polyargs->maxdigit) = vm["maxdigit"].as<int>(); //set maxdigit to the default value -1
  //   }

  // // special characters
  // if(vm.count("minspecial") && vm.count("maxspecial"))
  //   {
  //     *(polyargs->minspecial) = vm["minspecial"].as<int>();
  //     *(polyargs->maxspecial) = vm["maxspecial"].as<int>();
  //   }
  // else if(vm.count("maxspecial"))
  //   {
  //     *(polyargs->maxspecial) = vm["maxspecial"].as<int>();
  //     *(polyargs->minspecial) = 0;
  //   }
  // else
  //   {
  //     *(polyargs->minspecial) = vm["minspecial"].as<int>();
  //     *(polyargs->maxspecial) = vm["maxspecial"].as<int>(); //set maxspecial to the default value -1
  //   }

}


int main(int argc ,char* argv[])
{
    try
    {
        //IO parameters
        string wordlist;
        string output;
        string input;

        //print parameters
        bool hiderare;
        bool quiet;

        //password properties
        vector<string> charset;

        //length parameters
        int minlength;
        int maxlength;
        
        //unsigned int threads;

        po::options_description files("Files I/O");
        files.add_options()
            ("wordlist, w", po::value<string>(), "Wordlist.")
            ("output, o", po::value<string>(&output)->default_value("statsgen.masks"), "Ouput File.")
          ("input, i", po::value<string>(&input), "Input File.");


        po::options_description password("Password Structure");
        password.add_options()
            ("charset, c", po::value<vector<string>>(), "Password's charset.")
            ("minlength", po::value<int>(&minlength)->default_value(-1)->implicit_value(-1), "Minimum password length.")
            ("maxlength", po::value<int>(&maxlength)->default_value(-1)->implicit_value(-1), "Miximum password length.");        

        po::options_description print("Print");
        print.add_options()
            ("hiderare", po::value<bool>(&hiderare)->implicit_value(true)->default_value(false), "Omit items with occurrence of less than 1%.")
            ("quiet, q", po::value<bool>(&quiet)->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");

        // po::options_description parallel("Paralelization");
        // parallel.add_options()
        //     ("threads, t", po::value<unsigned int>(&threads)->default_value(2), "Number of threads.");

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

        if(vm.count("input"))
          {
            // write the support to read from a ini file
          }
        else
          {
            // input argument analysis
            statsargi arguments; // this variable modify all the other variables(lenght , upper, lower, special, quiet, ..)
            arguments.output = &output;

            arguments.quiet = &quiet;
            //arguments.show = &show;


            arguments.minlength = &minlength;
            arguments.maxlength = &maxlength;
            // arguments.minlower = &minlower;
            // arguments.minupper = &minupper;
            // arguments.maxupper = &maxupper;
            // arguments.mindigit = &mindigit;
            // arguments.maxdigit = &maxdigit;
            // arguments.minspecial = &minspecial;
            // arguments.maxspecial = &maxspecial;


            // read and analyze the entered arguments
            validate_arguments(vm, &arguments);
          }


        // Solve the support for multi arguments input for flag(vector<string> charset)
        //PPACK::statgen()
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}
