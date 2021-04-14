/*
 * pstruct ppack structs head file
 * pstruct implemented 24 nov 2020
 *
 *
 * Depuration:
 * rstruct and inheritance classes tested 27 nov 2020.
 *
 * No tested functions: ALL ClASES TESTED
 *
 * No implemented functions: ALL FUNCTIONS OR METHOD IMEPLEMENTED
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */

#ifndef _ARGS_H
#define _ARGS_H


#include<map>
#include <iostream>
#include <cstdlib>
#include <omp.h>
//#include <exception>

using namespace std;

#include<boost/program_options.hpp>

using namespace boost;
namespace po = boost::program_options;


#include "mask.hpp"

namespace ppack
{
  class Args
  {
  public:
    Args(){};
    Args(unsigned int min_length, int max_length,
         bool quietPrint,
         string outputFile, string inputFile);

    // password and mask
    unsigned int minlength;
    int maxlength;

    // print
    bool quiet;

    // io
    string input; // input file
    string output; //output file

    virtual void debug();
    ~Args(){}
  };

  // statsgen requirements struct
  class Sargs: public Args
  {
  public:
    Sargs(po::variables_map vm, po::options_description statsgen);
    Sargs(unsigned int min_length, int max_length, //mask struct arguements
         bool quiet_print, double hide_rare,          //print arguments
         string output_file, string input_file,     // IO arguements
         vector<string> scs,                  // characterset parameters
         vector<string> acs);                  // characterset parameters


    // password and mask
    //unsigned int minlength; - inheritance attribute
    //int maxlength; - inheritance attribute


    // print
    double hiderare;
    // bool quiet; - inheritance attribute

    // check requierement
    vector<SCS> scs;
    vector<ACS> acs;


    // io parameters
    string wordlist; // wordlist file
    // string input; // input options - inehritance attribute
    // string output; //output file of statsgen - inehritance attribute

    void debug();
  };


  // maskgen requirements struct
  class Margs: public Args
  {
  public:
    Margs(po::variables_map vm, po::options_description maskgen);
    Margs(unsigned int min_length, int max_length,             //
          unsigned int min_complexity, int max_complexity,     // mask struct parameters
          unsigned int min_occurence, int max_occurence,       //
          bool quiet_print, bool show_masks,                   // print parametersxs
          vector<string> scharsets, vector<string> acharsets,
          vector<Mask> checkmasks,string checkmasksfile,
          string output_file, string statgen_ouput);

    // password and mask
    //unsigned int minlength; - inheritance attribute
    //int maxlength; - inheritance attribute
    unsigned int mincomplexity;
    int maxcomplexity;

    unsigned int minoccurrence;
    int maxoccurrence;

    // print
    bool show;
    // bool quiet; - inheritance attribute

    // check
    vector<Mask> checkMasks;
    string checkMaskFile;
    vector<SCS> scs;
    vector<ACS> acs;

    // io
    //string input; // input options - inehritance attribute
    //string output; //output file of maskgen (generated masks) - inehritance attribute
    string statsgen; // output of statsgen method

    void debug();
  };


  // policygen requirements struct
  class Pargs:public Args
  {
  public:
    Pstruct(){};
    Pstruct(po::variables_map vm, po::options_description policygen);
    Pstruct(unsigned int min_length, int max_length,    //
            unsigned int min_lower, int max_lower,      // masks
            unsigned int min_upper, int max_upper,      // struct
            unsigned int min_digit, int max_digit,      // parameters
            unsigned int min_special, int max_special,  //
            bool quiet_print, bool show_masks,          // print parameters
            string output_file, string input_file,      // io parameters
            unsigned nthreads);

    // password and mask
    //unsigned int minlength; - inehritance attribute
    //int maxlength; - inehritance attribute
    unsigned int minlower;
    int maxlower;

    unsigned int minupper;
    int maxupper;

    unsigned int mindigit;
    int maxdigit;

    unsigned int minspecial;
    int maxspecial;

    // print
    //bool quiet; - inehritance attribute
    bool show;

    // io paramemters
    //string input; // requirement file - inehritance attribute
    //string output; //output file of policygen (generated masks) --inheritance attribute

    void debug(); // show all the parameters
  };
}
#endif //_ARGS_H
