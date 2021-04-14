/*
 * policygen - cli interface
 *
 * Depuration - 28 nov 2020
 * policygen (cli interface) depurate.
 *
 * No tested functions: NONE
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


#include <cstdlib>
#include <iostream>
using namespace std;

#include<boost/program_options.hpp>
#endif //__INCLUDE_PROGRAM_OPTIONS_H__
//using namespace boost;
namespace po = boost::program_options;


#include "../include/core/ppack.hpp"
#include "../include/args.hpp"


int main(int argc ,char* argv[])
{
  try
    {
      po::options_description files("Files I/O");
      files.add_options()
        ("output,o", po::value<string>()->default_value(""), "Ouput File.")
        ("input,i", po::value<string>()->default_value(""), "Input File.");

      po::options_description print("Print");
      print.add_options()
        ("show,s", po::value<bool>()->implicit_value(true)->default_value(false), "Show generated masks.")
        ("quiet,q", po::value<bool>()->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).")
        ("pretty,p", po::value<bool>()->implicit_value(true)->default_value(false), "Pretty output.");


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
        ("version,v", "PPACK version.")
        ("help,h", "Show help.");
      policygen.add(files).add(print).add(mask);

      po::variables_map vm;

      po::store(po::command_line_parser(argc, argv).
                options(policygen).run(), vm);

      if(vm.count("help")){
        cout << policygen << endl;
        exit(EXIT_FAILURE);
      }

      if(vm.count("version"))
        {
          //cout << "PPACK  version " + ppack::VERSION << endl;
          cout << "PPACK  version: 1.0"  << endl;
          exit(EXIT_FAILURE);
        }

      //cout << "before run pstruct constructor." << endl;
      Pargs pargs(vm, policygen);
      //pargs.debug();

      PPACK::policygen(pargs);
      return 0;
    }
  catch(std::exception& e)
    {
      cout << e.what() << endl;
      exit(EXIT_FAILURE);
    }
}
