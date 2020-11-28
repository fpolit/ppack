/*
 * pstruct ppack structs source file
 * pstruct implemented 24 nov 2020
 *
 *
 * Depuration:
 *
 *
 *
 * No tested functions:
 *
 *
 *
 * No implemented functions:
 *
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <cstdlib>
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__



#ifndef __INCLUDE_STD_EXCEPTION_H__
#define __INCLUDE_STD_EXCEPTION_H__
#include <exception>
#endif //__INCLUDE_STD_EXCEPTION_H__

using namespace std;


#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "../include/pstructs.hpp"
#endif // __INCLUDE_PSTRUCTS_H__

//////////////////////////////////
///// rstruct implementation /////
//////////////////////////////////

rstruct::rstruct(unsigned int min_length, int max_length,
                 bool quiet_print,
                 string output_file, string input_file)
{

  // mask struct
  minlength = min_length;
  maxlength = max_length;

  //print parameters
  quiet = quiet_print;

  // I/O paramemters
  output = output_file;
  input = input_file;
}

void rstruct::debug()
{
  cout << "debug rstruct\n\n";

  // file section
  cout << "--- file section ---"  << endl;
  cout << "input:  " << input << endl;
  cout << "output: " << output << endl;

  // print section
  cout << "\n--- print section ---"  << endl;
  cout << "quiet: " << quiet << endl;

  // mask section
  cout << "\n--- mask section ---"  << endl;
  cout << "minlenght:  " << minlength << endl;
  cout << "maxlength:  " << maxlength << endl;
}

//////////////////////////////////
///// sstruct implementation /////
//////////////////////////////////


sstruct::sstruct(unsigned int min_length, int max_length, //mask struct parameters
          bool quietPrint, bool hideRare,          //print parameters
          string output_file, string input_file,     // IO parameters
          vector<SCS> scharsets)                  // check parameters
  :rstruct(min_length, max_length,
           quietPrint,
           output_file, input_file)
{
  charsets = scharsets;
  hiderare = hideRare;
}

sstruct::sstruct(po::variables_map vm)
/*
 * init a sstruct with all the paramenters entered to vm
 * (from cli using flags)
 */
{
  ////////// Output File parameter(files section) //////////

  if(vm.count("wordlist"))
    wordlist = vm["wordlist"].as<string>();
  else
    {
      cerr << "No wordlist to analize." << endl;
      exit(EXIT_FAILURE); // no wordlist to analyze
    }

  // if there is a output paramenter assign to output attribute, 
  // otherwise assign the default value
  output = vm["output"].as<string>();

  // if there is a output paramenter assign to output attribute, 
  // otherwise assign the default value
  input = vm["input"].as<string>();

  ////////// print parameters(print section) //////////
  
  // if there is a quiet paramenter assign to quiet attribute, otherwise assign the default value
  quiet = vm["quiet"].as<bool>();

  // if there is a hiderare paramenter assign to hiderare attribute, otherwise assign the default value
  hiderare = vm["hiderare"].as<bool>();

  ////////// check parameters (check section) //////////
  // NO CHECK SECTION


  ////////// mask parameters (mask section) //////////
  //length
  minlength = vm["minlength"].as<unsigned int>();
  maxlength = vm["maxlength"].as<int>();

  try
  {
    if(minlength >0 && maxlength == 0)
      maxlength = -1; //there isn't a maximum length
    else if (minlength > 0 && maxlength != 0)
    {
      if(maxlength < 0)
          maxlength = -1;
      else
       {
         if((int)minlength > maxlength)
          throw "Invalid arguments(mask length).";
       }
    }
    else if (minlength == 0 && maxlength != 0)
    {
      if(maxlength < 0)
        maxlength = -1; //there isn't a maximum length
    } // else case is when minlength == 0 and maxlength == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }
}

void sstruct::debug()
{
    cout << "debug sstruct\n";

  // file section
  cout << "--- file section ---"  << endl;
  cout << "input:  " << input << endl;
  cout << "output: " << output << endl;
  cout << "wordlist: " << wordlist << endl;

  // print section
  cout << "\n--- print section ---"  << endl;
  cout << "quiet: " << quiet << endl;
  cout << "hiderare: " << hiderare << endl;

  // mask section
  cout << "\n--- mask section ---"  << endl;
  cout << "minlenght:  " << minlength << endl;
  cout << "maxlength:  " << maxlength << endl;

  // check requirements
  cout << "chasets:";
  for(SCS charset: charsets)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << charset << ", "; 
  cout << endl;
}

//////////////////////////////////
///// mstruct implementation /////
//////////////////////////////////


mstruct::mstruct(po::variables_map vm)
/*
 * init a mstruct with all the paramenters entered to vm
 * (from cli using flags)
 */
{
  ////////// Output File parameter(files section) //////////

  if(vm.count("statsgen"))
    statsgen = vm["statsgen"].as<string>();
  else
    {
      cerr << "No statsgen's output to analize." << endl;
      exit(EXIT_FAILURE); // no wordlist to analyze
    }

  // if there is a output paramenter assign to output attribute, 
  // otherwise assign the default value
  output = vm["output"].as<string>();

  // if there is a input paramenter assign to output attribute, 
  // otherwise assign the default value
  input = vm["input"].as<string>();

  ////////// print parameters(print section) //////////
  
  // if there is a quiet paramenter assign to quiet attribute, otherwise assign the default value
  quiet = vm["quiet"].as<bool>();

  // if there is a show paramenter assign to show attribute, otherwise assign the default value
  show = vm["show"].as<bool>();

  ////////// check parameters (check section) //////////
  if(vm.count("checkmasks"))
    checkMasks = vm["checkmasks"].as<vector<Mask>>();

  if(vm.count("checkmasksfile"))
    checkMaskFile = vm["checkmasksfile"].as<string>();

  ////////// password parameters (password section) //////////
  // charsets
  if(vm.count("scharset"))
    charsets = vm["scharset"].as<vector<SCS>>();

  if(vm.count("acharset"))
    advCharsets = vm["acharset"].as<vector<ACS>>();
  
  //length
  minlength = vm["minlength"].as<unsigned int>();
  maxlength = vm["maxlength"].as<int>();

  try
  {
    if(minlength >0 && maxlength == 0)
      maxlength = -1; //there isn't a maximum length
    else if (minlength > 0 && maxlength != 0)
    {
      if(maxlength < 0)
          maxlength = -1;
      else
       {
         if((int)minlength > maxlength)
          throw "Invalid arguments(mask length).";
       }
    }
    else if (minlength == 0 && maxlength != 0)
    {
      if(maxlength < 0)
        maxlength = -1; //there isn't a maximum length
    } // else case is when minlength == 0 and maxlength == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }

  //complexity : IMPLEMENT COMPLEXITU ANALYSIS
  mincomplexity = vm["mincomplexity"].as<unsigned int>();
  maxcomplexity = vm["maxcomplexity"].as<int>();

  ////////// frequency parameters (frequency section) //////////
  //occurence
  minoccurence = vm["minoccurence"].as<unsigned int>();
  maxoccurence = vm["maxoccurence"].as<int>();

  try
  {
    if(minoccurence >0 && maxoccurence == 0)
      maxoccurence = -1; //there isn't a maximum occurence
    else if (minoccurence > 0 && maxoccurence != 0)
    {
      if(maxoccurence < 0)
          maxoccurence = -1;
      else
       {
         if((int)minoccurence > maxoccurence)
          throw "Invalid arguments(mask occurence).";
       }
    }
    else if (minoccurence == 0 && maxoccurence != 0)
    {
      if(maxoccurence < 0)
        maxoccurence = -1; //there isn't a maximum length
    } // else case is when minoccurence == 0 and maxoccurence == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }
}

mstruct::mstruct(unsigned int min_length, int max_length,             //
          unsigned int min_complexity, int max_complexity,     // mask struct parameters
          unsigned int min_occurence, int max_occurence,       //
          bool quiet_print, bool show_masks,                   // print parametersxs
          vector<SCS> scharsets,
          vector<Mask> check_masks,string check_mask_file,
          string output_file, string statsgen_output)
  :rstruct(min_length, max_length,
           quiet_print,
           output_file, statsgen_output)
{

  // password and mas structure requirements
  mincomplexity = min_complexity;
  maxcomplexity = max_complexity;
  minoccurence = min_occurence;
  maxoccurence = max_occurence;

  // print parameters
  show = show_masks;
  quiet = quiet_print;

  // check requierement
  checkMasks = check_masks;
  checkMaskFile = check_mask_file;
  charsets = scharsets;
}

void mstruct::debug()
{
  cout << "debug sstruct\n";

  // file section
  cout << "--- file section ---"  << endl;
  cout << "input    :  " << input << endl;
  cout << "output   : " << output << endl;
  cout << "statsgen : " << statsgen << endl;

  // print section
  cout << "\n--- print section ---"  << endl;
  cout << "quiet: " << quiet << endl;
  cout << "show : " << show << endl;


  // check requirements
  cout << "\n--- check section ---"  << endl;
  cout << "checkMasks:";
  for(Mask mask: checkMasks)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << mask << ", "; 
  cout << endl;
  
  cout << "checkMaskFile:" << checkMaskFile << endl;
  

  // password section
  cout << "\n--- password section ---"  << endl;
  cout << "schasets:";
  for(SCS charset: charsets)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << charset << ", "; 
  cout << endl;

  cout << "advChasets:";
  for(ACS acharset: advCharsets)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << acharset << ", "; 
  cout << endl;

  cout << "minlenght:  " << minlength << endl;
  cout << "maxlength:  " << maxlength << endl;
  
  cout << "mincomplexity:  " << mincomplexity << endl;
  cout << "maxcomplexity:  " << maxcomplexity << endl;

  // frequency section
  cout << "\n--- frequency section ---"  << endl;
  cout << "minoccurence:  " << minoccurence << endl;
  cout << "maxoccurence:  " << maxoccurence << endl;
}


//////////////////////////////////
///// pstruct implementation /////
//////////////////////////////////


pstruct::pstruct(unsigned int min_length, int max_length,    //
                 unsigned int min_lower, int max_lower,      // masks
                 unsigned int min_upper, int max_upper,      // struct
                 unsigned int min_digit, int max_digit,      // parameters
                 unsigned int min_special, int max_special,  // 
                 bool quiet_print, bool show_masks,          // print parameters
                 string output_file, string input_file)      // io parameters
  :rstruct(min_length, max_length,
           quiet_print,
           output_file, input_file)
{
  // masks struct parameters
  minlower = min_lower;
  maxlower = max_lower;

  minupper = min_upper;
  maxupper = max_upper;

  mindigit = min_digit;
  maxdigit = max_digit;

  minspecial = min_special;
  maxspecial = max_special;

  // print parameters
  show = show_masks;
}

pstruct::pstruct(po::variables_map vm)
/*
 * init a pstruct with all the paramenters entered to vm
 * (from cli using flags)
 */
{
  ////////// Output File parameter(files section) //////////
  
  // if there is a output paramenter assign to output attribute, 
  // otherwise assign the default value
  output = vm["output"].as<string>();

  // if there is a output paramenter assign to output attribute, 
  // otherwise assign the default value
  input = vm["input"].as<string>();

  
  ////////// print parameters(print section) //////////
  
  // if there is a quiet paramenter assign to quiet attribute, otherwise assign the default value
  quiet = vm["quiet"].as<bool>();

  // if there is a show paramenter assign to show attribute, otherwise assign the default value
  show = vm["show"].as<bool>();

  ////////// mask parameters (mask section) //////////
  //length
  minlength = vm["minlength"].as<unsigned int>();
  maxlength = vm["maxlength"].as<int>();

  try
  {
    if(minlength >0 && maxlength == 0)
      maxlength = -1; //there isn't a maximum length
    else if (minlength > 0 && maxlength != 0)
    {
      if(maxlength < 0)
          maxlength = -1;
      else
       {
         if((int)minlength > maxlength)
          throw "Invalid arguments(mask length).";
       }
    }
    else if (minlength == 0 && maxlength != 0)
    {
      if(maxlength < 0)
        maxlength = -1; //there isn't a maximum length
    } // else case is when minlength == 0 and maxlength == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }
  
  //  complexity 
  // mincomplexity = vm["mincomplexity"].as<unsigned int>();
  // maxcomplexity = vm["maxcomplexity"].as<int>();

  // try
  // {
  //   if(minspecial >0 && maxspecial == 0)
  //     maxspecial = -1; //there isn't a maximum special  characters
  //   else if (minspecial > 0 && maxspecial != 0)
  //   {
  //     if(maxspecial > 0 && (int)minspecial > maxspecial)
  //       throw "Invalid arguments(mask special characters).";

  //     else
  //       maxspecial = -1; //there isn't a maximum special charaters
  //   }
  //   else if (minspecial == 0 && maxspecial != 0)
  //   {
  //     if(maxspecial < 0)
  //       maxspecial = -1; //there isn't a maximum special characters
  //   }// else case is when minspecial == 0 and maxspecial == 0
  // }
  // catch(std::exception &error)
  // {
  //   cout << error.what() << endl;
  //   exit(1);
  // }

  // lower characters
  minlower = vm["minlower"].as<unsigned int>();
  maxlower = vm["maxlower"].as<int>();

  try
  {
    if(minlower >0 && maxlower == 0)
      maxlower = -1; //there isn't a maximum lowercases
    else if (minlower > 0 && maxlower != 0)
    {
      if(maxlower < 0)
        maxlower = -1; //there isn't a maximum lowercase
      else
      {
        if((int)minlower > maxlower)
        throw "Invalid arguments(mask lower cases).";
      }
    }
    else if (minlower == 0 && maxlower != 0)
    {
      if(maxlower < 0)
        maxlower = -1; //there isn't a maximum lowercases
    }// else case is when minlower == 0 and maxlower == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }

  // upper characters
  minupper = vm["minupper"].as<unsigned int>();
  maxupper = vm["maxupper"].as<int>();

  try
  {
    if(minupper >0 && maxupper == 0)
      maxupper = -1; //there isn't a maximum uppercases
    else if (minupper > 0 && maxupper != 0)
    {
      if(maxupper < 0)
        maxupper = -1; //there isn't a maximum uppercases
      else
      {
        if((int)minupper > maxupper)
        throw "Invalid arguments(mask uppercases).";
      }
    }
    else if (minupper == 0 && maxupper != 0)
    {
      if(maxupper < 0)
        maxupper = -1; //there isn't a maximum uppercases
    }// else case is when minupper == 0 and maxupper == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }

  // digit characters
  mindigit = vm["mindigit"].as<unsigned int>();
  maxdigit = vm["maxdigit"].as<int>();

  try
  {
    if(mindigit >0 && maxdigit == 0)
      maxdigit = -1; //there isn't a maximum digits
    else if (mindigit > 0 && maxdigit != 0)
    {
      if(maxdigit < 0)
        maxdigit = -1; //there isn't a maximum digits
      else
      {
        if((int)mindigit > maxdigit)
          throw "Invalid arguments(mask digits).";
      }
    }
    else if (mindigit == 0 && maxdigit != 0)
    {
      if(maxdigit < 0)
        maxdigit = -1; //there isn't a maximum digits
    }// else case is when mindigit == 0 and maxdigit == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }

  // special characters
  minspecial = vm["minspecial"].as<unsigned int>();
  maxspecial = vm["maxspecial"].as<int>();

  try
  {
    if(minspecial >0 && maxspecial == 0)
      maxspecial = -1; //there isn't a maximum special  characters
    else if (minspecial > 0 && maxspecial != 0)
    {
      if(maxspecial < 0)
        maxspecial = -1; //there isn't a maximum special characters
      else
      {
        if((int)minspecial > maxspecial)
        throw "Invalid arguments(mask special characters).";
      }
    }
    else if (minspecial == 0 && maxspecial != 0)
    {
      if(maxspecial < 0)
        maxspecial = -1; //there isn't a maximum special characters
    }// else case is when minspecial == 0 and maxspecial == 0
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }
}


void pstruct::debug() // show all the parameters
{
  cout << "debug pstruct\n\n";

  // file section
  cout << "--- file section ---"  << endl;
  cout << "input:  " << input << endl;
  cout << "output: " << output << endl;

  // print section
  cout << "\n--- print section ---"  << endl;
  cout << "show:  " << show << endl;
  cout << "quiet: " << quiet << endl;

  // mask section
  cout << "\n--- mask section ---"  << endl;
  cout << "minlenght:  " << minlength << endl;
  cout << "maxlength:  " << maxlength << endl;

  cout << "minlower:   " << minlower << endl;
  cout << "maxlower:   " << maxlower << endl;

  cout << "minupper:   " << minupper << endl;
  cout << "maxupper:   " << maxupper << endl;

  cout << "mindigit:   " << mindigit << endl;
  cout << "maxdigit:   " << maxdigit << endl;

  cout << "minspecial: " << minspecial << endl;
  cout << "maxspecial: " << maxspecial << endl;
}