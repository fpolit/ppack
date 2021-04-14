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

#include <iostream>
#include<vector>
using namespace std;

#include<boost/program_options.hpp>
namespace po = boost::program_options;


#include "../include/core/ppack.hpp"
#include "../include/args.hpp"


int main(int argc ,char* argv[])
{
  try
  {
    po::options_description files("Files I/O");
    files.add_options()
        ("wordlist,w", po::value<string>(), "Wordlist File.")
        ("output,o", po::value<string>()->default_value(""), "Ouput File.")
      ("input,i", po::value<string>(), "Input File.");


    po::options_description password("Password Structure");

    // string help_scs =   "Simple charset.\n" +
    //                     "Availables scs:\n" +
    //                     "\tloweralpha,upperalpha,numeric,special,alpha,\n" +
    //                     "\tmixalphaspecial,mixalphanum,mixspecialnum,mixall";

    // string help_acs =   "Advance charset.\n" +
    //                     "Availables acs:\n"  +
    //                     "\talphaspecial,loweralphaspecial,upperalphaspecial,\n" +
    //                     "\tspecialalpha,specialloweralpha,specialupperalpha,\n" +
    //                     "\talphanum,loweralphanum,upperalphanum,specialnum,numspecial";

    password.add_options()
        ("scs", po::value<vector<string>>(), "Simple charset.")
        ("acs", po::value<vector<string>>(), "Advance charset.")
        ("minlength", po::value<unsigned int>()->default_value(0), "Minimum password length.")
        // if no length option entered minlength=0 and maxlength=-1 (without eny filter of length)
        ("maxlength", po::value<int>()->default_value(-1), "Miximum password length.");

    po::options_description print("Print");
    print.add_options()
        ("hiderare,r", po::value<double>()->default_value(0.0), "Omit items with occurrence lower that you supplied.")
        ("quiet,q", po::value<bool>()->implicit_value(true)->default_value(false), "Quiet printing(Omit PPACK logo).")
        ("pretty,p", po::value<bool>()->implicit_value(true)->default_value(false), "Pretty output.");

    po::options_description statsgen("Generate statistic of a wordlists that help you crack passwords");
    statsgen.add_options()
        ("version,v", "PPACK version.")
        ("help,h", "Show help.");
    statsgen.add(files).add(password).add(print);

    po::variables_map vm;

    store(po::command_line_parser(argc, argv).
            options(statsgen).run(), vm);

    if(vm.count("help"))
      {
        cout << statsgen << endl;
        return 1;
      }

    if(vm.count("version"))
      {
        cout << "PPACK  version " + VERSION << endl;
        return 1;
      }


    Sargs sargs(vm, statsgen);
    //sargs.debug();

    PPACK::statsgen(sargs);
    return 0;
  }
  catch(std::exception& e)
  {
    cout << e.what() << endl;
    return 1;
  }
}
