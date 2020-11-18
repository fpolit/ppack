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


#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../include/ppack.hpp"
#endif // __INCLUDE_PPACK_H__

using namespace std;


typedef struct argi{
  string *output;                       //Output File
  bool *quiet; bool *show;                           //print parameters
  int *minlength; int *maxlength;                         //length parameters
  int *minlower; int *maxlower;                           //
  int *minupper; int *maxupper;                           // password
  int *mindigit; int *maxdigit;                           // charset
  int *minspecial; int *maxspecial;
}argi;

void validate_arguments(po::variables_map vm, argi *polyargs)
/*
 * Validate the process of flag reading and set default value to forgeted parameters
 * also assign these validated parameters to their varibles
 */
{
  //Output File parameter(files section)
  if(vm.count("output"))
    {
      *(polyargs->output) = vm["output"].as<string>();
    }

  //print parameters(print section)
  if(vm.count("quiet"))
    {
      *(polyargs->quiet) = vm["quiet"].as<bool>();
    }

  if(vm.count("show"))
    {
      *(polyargs->show) = vm["show"].as<bool>();
    }

  //length parameters (mask section)
  if(vm.count("minlength") && vm.count("maxlength"))
    {
      *(polyargs->minlength) = vm["minlength"].as<int>();
      *(polyargs->maxlength) = vm["maxlength"].as<int>();
    }
  else if(vm.count("maxlength"))
    {
      *(polyargs->maxlength) = vm["maxlength"].as<int>();
      *(polyargs->minlength) = 0;
    }
  else
    {
      *(polyargs->minlength) = vm["minlength"].as<int>();
      *(polyargs->maxlength) = vm["maxlength"].as<int>(); //set maxlength to the default value -1
    }

  // password complexity requirements (mask section)

  // lower characters
  if(vm.count("minlower") && vm.count("maxlower"))
    {
      *(polyargs->minlower) = vm["minlower"].as<int>();
      *(polyargs->maxlower) = vm["maxlower"].as<int>();
    }
  else if(vm.count("maxlower"))
    {
      *(polyargs->maxlower) = vm["maxlower"].as<int>();
      *(polyargs->minlower) = 0;
    }
  else
    {
      *(polyargs->minlower) = vm["minlower"].as<int>();
      *(polyargs->maxlower) = vm["maxlower"].as<int>(); //set maxlower to the default value -1
    }

  // upper characters
  if(vm.count("minupper") && vm.count("maxupper"))
    {
      *(polyargs->minupper) = vm["minupper"].as<int>();
      *(polyargs->maxupper) = vm["maxupper"].as<int>();
    }
  else if(vm.count("maxupper"))
    {
      *(polyargs->maxupper) = vm["maxupper"].as<int>();
      *(polyargs->minupper) = 0;
    }
  else
    {
      *(polyargs->minupper) = vm["minupper"].as<int>();
      *(polyargs->maxupper) = vm["maxupper"].as<int>(); //set maxupper to the default value -1
    }

  // digit characters
  if(vm.count("mindigit") && vm.count("maxdigit"))
    {
      *(polyargs->mindigit) = vm["mindigit"].as<int>();
      *(polyargs->maxdigit) = vm["maxdigit"].as<int>();
    }
  else if(vm.count("maxdigit"))
    {
      *(polyargs->maxdigit) = vm["maxdigit"].as<int>();
      *(polyargs->mindigit) = 0;
    }
  else
    {
      *(polyargs->mindigit) = vm["mindigit"].as<int>();
      *(polyargs->maxdigit) = vm["maxdigit"].as<int>(); //set maxdigit to the default value -1
    }

  // special characters
  if(vm.count("minspecial") && vm.count("maxspecial"))
    {
      *(polyargs->minspecial) = vm["minspecial"].as<int>();
      *(polyargs->maxspecial) = vm["maxspecial"].as<int>();
    }
  else if(vm.count("maxspecial"))
    {
      *(polyargs->maxspecial) = vm["maxspecial"].as<int>();
      *(polyargs->minspecial) = 0;
    }
  else
    {
      *(polyargs->minspecial) = vm["minspecial"].as<int>();
      *(polyargs->maxspecial) = vm["maxspecial"].as<int>(); //set maxspecial to the default value -1
    }

}


int main(int argc ,char* argv[])
{
    try
    {
        //Output File parameter(files)
        string output;
        string input; // ini file

        //print parameters(print)
        bool quiet;
        bool show;

        //length parameters (mask section)
        int minlength;
        int maxlength;

        // password complexity requirements (mask section)
        int minlower;
        int maxlower;
        int minupper;
        int maxupper;
        int mindigit;
        int maxdigit;
        int minspecial;
        int maxspecial;



        po::options_description files("Files I/O");
        files.add_options()
            ("output, o", po::value<string>(&output)->default_value("policygen.hcmasks"), "Ouput File.")
          ("input, i", po::value<string>(&input), "Input File.");

        po::options_description print("Print");
        print.add_options()
            ("show", po::value<bool>(&show)->implicit_value(true)->default_value(false), "Show generated masks.")
            ("quiet, q", po::value<bool>(&quiet)->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).");


        po::options_description mask("Mask Structure");

        // means of -1 value as default value:
        // examples(we use lower as a concrete case, but this can be used equal for other cases[upper, digit and special also length]):
        // minlower = -1; means that the password haven't loweralpha characteres
        // maxlower = -1; means that the maximun number of loweralpha character is undifined
        // (if minlower=3 and (maxlower isn't entered)maxlower=-1 this means that the generated mask can have from 3 to more lower alpha)
        // (if minlower and maxlower isn't entered: then minlower=-1  that means that the password haven't loweralpha charactes even though maxlower=-1)
        // we create this rule to avoid enter unnecesary flags as --minlower=0 to avoid lower character, instead of that you only have to don't enter the flag related to lowers
        // If you forgot enter the flag --minlower but you enter --maxlower=MAXIMUN_LOWERS, then automatically minlower=0 (instead of the default value -1)



        mask.add_options()
            ("minlength", po::value<int>(&minlength)->default_value(-1), "Minimum password length.")
            ("maxlength", po::value<int>(&maxlength)->default_value(-1), "Maximum password length.")

            ("minlower", po::value<int>(&minlower)->default_value(-1), "Minimum password lowercase characters.")
            ("maxlength", po::value<int>(&maxlower)->default_value(-1), "Maximum password lowercase characters.")

            ("minupper", po::value<int>(&minupper)->default_value(-1), "Minimum password uppercase characters.")
            ("maxupper", po::value<int>(&maxupper)->default_value(-1), "Maximum password uppercase characters.")


            ("mindigit", po::value<int>(&mindigit)->default_value(-1), "Minimum password digits characters.")
            ("maxdigit", po::value<int>(&maxdigit)->default_value(-1), "Maximum password digits characters.")

            ("minspecial", po::value<int>(&minspecial)->default_value(-1), "Minimum password special characters.")
            ("maxspecial", po::value<int>(&maxspecial)->default_value(-1), "Maximum password special characters.");

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
          cout << "PPACK  version: " << PPACK_VERSION  << endl;
            return 1;
        }

        if(vm.count("input"))
          {
            // write the support to read from a ini file
          }
        else
          {
            // input argument analysis
            argi arguments; // this variable modify all the other variables(lenght , upper, lower, special, quiet, ..)
            arguments.output = &output;

            arguments.quiet = &quiet;
            arguments.show = &show;


            arguments.minlength = &minlength;
            arguments.maxlength = &maxlength;
            arguments.minlower = &minlower;
            arguments.minupper = &minupper;
            arguments.maxupper = &maxupper;
            arguments.mindigit = &mindigit;
            arguments.maxdigit = &maxdigit;
            arguments.minspecial = &minspecial;
            arguments.maxspecial = &maxspecial;


            // read and analyze the entered arguments
            validate_arguments(vm, &arguments);
          }

        PPACK::policygen(output,                        //Output File
                        quiet,      show,               //print parameters
                        minlength,  maxlength,          //length parameters
                        minlower,   maxlower,           //
                        minupper,   maxupper,           // password
                        mindigit,   maxdigit,           // charset
                         minspecial, maxspecial);       //
        return 0;
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
}
