/*
 * pstruct ppack structs source file
 * pstruct implemented 24 nov 2020
 *
 *
 * Depuration: Dec 12 2020 
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */



#ifndef __INCLUDE_PSTRUCTS_H__
#define __INCLUDE_PSTRUCTS_H__
#include "../include/pstructs.hpp"
#include <cstdlib>
#include <exception>
#endif // __INCLUDE_PSTRUCTS_H__


class InvalidCharset : public std::exception
{
  private:
    string scharset;

  public:
    InvalidCharset(string pscs)
    {
      scharset = pscs;
    }
    const char* what() const throw()
    {
      //return "Invalid SCS type : " + scharset;
      return "Invalid SCS type";
    }
};



//////////////////////////////////
///// rstruct implementation /////
//////////////////////////////////

rstruct::rstruct(unsigned int min_length, int max_length,
                 bool quiet_print,
                 string output_file, string input_file,
                 unsigned int nthreads)
{

  // mask struct
  minlength = min_length;
  maxlength = max_length;

  //print parameters
  quiet = quiet_print;

  // I/O paramemters
  output = output_file;
  input = input_file;

  // parallel parameters
  threads = nthreads;
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

  //parallel section
  cout << "\n--- parallel section --" << endl;
  cout << "threads: " << threads << endl;
}

//////////////////////////////////
///// sstruct implementation /////
//////////////////////////////////


sstruct::sstruct(unsigned int min_length, int max_length, //mask struct parameters
          bool quietPrint, double hideRare,          //print parameters
          string output_file, string input_file,     // IO parameters
          vector<string> scharsets,
          vector<string> acharsets,                  // check parameters
          unsigned int nthreads)
  :rstruct(min_length, max_length,
           quietPrint,
           output_file, input_file,
           nthreads)
{
  try {
    for(auto charset: scharsets)
    {
      SCS scharset = Mask::checkSCS(charset);
      if(SCS::none == scharset)
        throw InvalidCharset(charset);
      scs.push_back(scharset);
    }

    for(auto charset: acharsets)
    {
      ACS acharset = Mask::checkACS(charset);
      if(ACS::advnone == acharset)
        throw InvalidCharset(charset);
      acs.push_back(acharset);
    }

    hiderare = hideRare;

  } catch (std::exception& error) {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }
}

sstruct::sstruct(po::variables_map vm, po::options_description statsgen)
/*
 * init a sstruct with all the paramenters entered to vm
 * (from cli using flags)
 */
{
  ////////// Output File parameter(files section) //////////

// if there is a input paramenter assign to input attribute,
  // and read flags from it ini file
  // otherwise assign the default value ("")
  if(vm.count("input"))
  {
    // try{
    //   input = vm["input"].as<string>();
    //   CSimpleIniA filterFile;
    //   filterFile.SetUnicode();
    //   SI_Error rc = filterFile.LoadFile(input.c_str());
    //   if(rc < 0)
    //     throw std::exception();

    //   CSimpleIniA::TNamesDepend filters;
    //   filterFile.GetAllKeys("statsgen", filters);
    //   cout << "readed keys." << endl;
    // }
    // catch(std::exception& error)
    // {
    //   cout << error.what() << endl;
    //   cout << statsgen << endl;
    //   exit(EXIT_FAILURE);
    // }
  }
  else {
    try{
      if(vm.count("wordlist"))
        wordlist = vm["wordlist"].as<string>();
      else
      {
        throw Exception("No wordlist to analize.");
      }

      // if there is a output paramenter assign to output attribute, 
      // otherwise assign the default value
      output = vm["output"].as<string>();

      

      ////////// print parameters(print section) //////////
      
      // if there is a quiet paramenter assign to quiet attribute, otherwise assign the default value
      quiet = vm["quiet"].as<bool>();
    

      // if there is a hiderare paramenter assign to hiderare attribute, otherwise assign the default value
      if(vm.count("hiderare"))
        hiderare = vm["hiderare"].as<double>();

      // if there is a pretty paramenter assign to pretty attribute, otherwise assign the default value
      pretty = vm["pretty"].as<bool>();
    
      ////////// password parameters (password section) //////////
      // charsets
      if(vm.count("scs"))
      {
        for(auto charset: vm["scs"].as<vector<string>>())
        {
          SCS scharset = Mask::checkSCS(charset);
          if(SCS::none == scharset)
            throw InvalidCharset(charset);
          scs.push_back(scharset);
        }
      }
    

      if(vm.count("acs"))
      {
        for(auto charset: vm["acs"].as<vector<string>>())
        {
          ACS scharset = Mask::checkACS(charset);
          if(ACS::advnone == scharset)
            throw InvalidCharset(charset);
          acs.push_back(scharset);
        }
     }


      ////////// mask parameters (mask section) //////////
      //length
      minlength = vm["minlength"].as<unsigned int>();
      maxlength = vm["maxlength"].as<int>();

      if(minlength >0 && maxlength == 0)
        maxlength = -1; //there isn't a maximum length
      else if (minlength > 0 && maxlength != 0)
      {
        if(maxlength < 0)
            maxlength = -1;
        else
        {
          if((int)minlength > maxlength)
            throw Exception("Invalid arguments(mask length).");
        }
      }
      else if (minlength == 0 && maxlength != 0)
      {
        if(maxlength < 0)
          maxlength = -1; //there isn't a maximum length
      } // else case is when minlength == 0 and maxlength == 0
    
      ////////// parallel parameters (parallel section) //////////
      // threads = vm["threads"].as<unsigned int>();
      // int maxthreads = omp_get_max_threads();
      // if((int)threads > maxthreads)
      //   throw Exception("You haven't enough threads(max threads: " + to_string(maxthreads) + ")");
    }
    catch(std::exception &error)
    {
      cout << error.what() << endl;
      cout << statsgen << endl;
      exit(EXIT_FAILURE);
    }
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
  cout << "scs:";
  for(SCS charset: scs)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << charset << ", ";
  cout << endl;

  cout << "acs:";
  for(ACS charset: acs)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << charset << ", ";
  cout << endl;

  //parallel section
  cout << "\n--- parallel section --" << endl;
  cout << "threads: " << threads << endl;
}

//////////////////////////////////
///// mstruct implementation /////
//////////////////////////////////

mstruct::mstruct(unsigned int min_length, int max_length,             //
          unsigned int min_complexity, int max_complexity,     // mask struct parameters
          unsigned int min_occurrence, int max_occurrence,       //
          bool quiet_print, bool show_masks,                   // print parametersxs
          vector<string> scharsets, vector<string> acharsets,
          vector<Mask> check_masks,string check_mask_file,
          string output_file, string statsgen_output,
          unsigned int nthreads)
  :rstruct(min_length, max_length,
           quiet_print,
           output_file, statsgen_output,
           nthreads)
{
  try {
    for(auto charset: scharsets)
    {
      SCS scharset = Mask::checkSCS(charset);
      if(SCS::none == scharset)
        throw InvalidCharset(charset);
      scs.push_back(scharset);
    }

    for(auto charset: acharsets)
    {
      ACS acharset = Mask::checkACS(charset);
      if(ACS::advnone == acharset)
        throw InvalidCharset(charset);
      acs.push_back(acharset);
    }
    // password and mas structure requirements
    mincomplexity = min_complexity;
    maxcomplexity = max_complexity;
    minoccurrence = min_occurrence;
    maxoccurrence = max_occurrence;

    // print parameters
    show = show_masks;
    quiet = quiet_print;

    // check requierement
    for(auto mask: check_masks)
    {
      if(Mask::ismask(mask))
        throw InvalidMask(mask);
      checkMasks.push_back(Mask(mask));
    }

    checkMaskFile = check_mask_file;

  } catch (std::exception& error) {
    cout << error.what() << endl;
    exit(EXIT_FAILURE);
  }
}

mstruct::mstruct(po::variables_map vm, po::options_description maskgen)
/*
 * init a mstruct with all the paramenters entered to vm
 * (from cli using flags)
 */
{
  ////////// Output File parameter(files section) //////////
  try{
    if(vm.count("statsgen"))
      statsgen = vm["statsgen"].as<string>();
    else
      throw Exception("No statsgen's output to analize.");

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

    // if there is a pretty paramenter assign to pretty attribute, otherwise assign the default value
    pretty = vm["pretty"].as<bool>();

    ////////// check parameters (check section) //////////
    if(vm.count("checkmasks"))
    {

        for(string mask : vm["checkmasks"].as<vector<string>>())
        {
          if(!Mask::ismask(mask))
            throw InvalidMask(mask);  
          checkMasks.push_back(Mask(mask));
        }
    }

    if(vm.count("checkmasksfile"))
      checkMaskFile = vm["checkmasksfile"].as<string>();

    ////////// password parameters (password section) //////////
    // charsets
    if(vm.count("scs"))
    {

      for(auto charset: vm["scs"].as<vector<string>>())
      {
        SCS scharset = Mask::checkSCS(charset);
        if(SCS::none == scharset)
          throw InvalidCharset(charset);
        scs.push_back(scharset);
      }
    }

    if(vm.count("acs"))
    {
      for(auto charset: vm["acs"].as<vector<string>>())
      {
        ACS scharset = Mask::checkACS(charset);
        if(ACS::advnone == scharset)
          throw InvalidCharset(charset);
        acs.push_back(scharset);
      }
    }
  
    //length
    minlength = vm["minlength"].as<unsigned int>();
    maxlength = vm["maxlength"].as<int>();

    if(minlength >0 && maxlength == 0)
      maxlength = -1; //there isn't a maximum length
    else if (minlength > 0 && maxlength != 0)
    {
      if(maxlength < 0)
          maxlength = -1;
      else
       {
         if((int)minlength > maxlength)
          throw Exception("Invalid arguments(mask length).");
       }
    }
    else if (minlength == 0 && maxlength != 0)
    {
      if(maxlength < 0)
        maxlength = -1; //there isn't a maximum length
    } // else case is when minlength == 0 and maxlength == 0

    //complexity : IMPLEMENT COMPLEXITY ANALYSIS
    mincomplexity = vm["mincomplexity"].as<unsigned int>();
    maxcomplexity = vm["maxcomplexity"].as<int>();

    ////////// frequency parameters (frequency section) //////////
    //occurence
    minoccurrence = vm["minoccurrence"].as<unsigned int>();
    maxoccurrence = vm["maxoccurrence"].as<int>();

    if(minoccurrence >0 && maxoccurrence == 0)
      maxoccurrence = -1; //there isn't a maximum occurence
    else if (minoccurrence > 0 && maxoccurrence != 0)
    {
      if(maxoccurrence < 0)
          maxoccurrence = -1;
      else
       {
         if((int)minoccurrence > maxoccurrence)
          throw Exception("Invalid arguments(mask occurence).");
       }
    }
    else if (minoccurrence == 0 && maxoccurrence != 0)
    {
      if(maxoccurrence < 0)
        maxoccurrence = -1; //there isn't a maximum length
    } // else case is when minoccurence == 0 and maxoccurence == 0

    ////////// parallel parameters (parallel section) //////////
    // threads = vm["threads"].as<unsigned int>();
    // int maxthreads = omp_get_max_threads();
    // if((int)threads > maxthreads)
    //   throw Exception("You haven't enough threads(max threads: " + to_string(maxthreads) + ")");
  
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    cout << maskgen << endl;
    exit(EXIT_FAILURE);
  }
}

void mstruct::debug()
{
  cout << "debug mstruct\n";

  // file section
  cout << "--- file section ---"  << endl;
  cout << "statsgen : " << statsgen << endl;
  cout << "output   : " << output << endl;
  cout << "input    :  " << input << endl;


  // print section
  cout << "\n--- print section ---"  << endl;
  cout << "show  : " << show << endl;
  cout << "quiet : " << quiet << endl;
  cout << "pretty: " << pretty << endl;


  // check requirements
  cout << "\n--- check section ---"  << endl;
  cout << "checkMasks:";
  for(Mask mask: checkMasks)
    cout << mask << ", "; 
  cout << endl;
  
  cout << "checkMaskFile:" << checkMaskFile << endl;

  // password section
  cout << "\n--- password section ---"  << endl;
  cout << "scs:";
  for(SCS charset: scs)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << charset << ", "; 
  cout << endl;

  cout << "acs:";
  for(ACS acharset: acs)
  //scsValue is in mask.cpp(ans mask.hpp was included)
    cout << acharset << ", "; 
  cout << endl;

  cout << "minlenght:  " << minlength << endl;
  cout << "maxlength:  " << maxlength << endl;
  
  cout << "mincomplexity:  " << mincomplexity << endl;
  cout << "maxcomplexity:  " << maxcomplexity << endl;

  // frequency section
  cout << "\n--- frequency section ---"  << endl;
  cout << "minoccurence:  " << minoccurrence << endl;
  cout << "maxoccurence:  " << maxoccurrence << endl;

    //parallel section
  cout << "\n--- parallel section --" << endl;
  cout << "threads: " << threads << endl;
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
                 string output_file, string input_file,      // io parameters
                unsigned int nthreads)
                :rstruct(min_length, max_length,
                          quiet_print,
                          output_file, input_file,
                          nthreads)
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

pstruct::pstruct(po::variables_map vm, po::options_description policygen)
/*
 * init a pstruct with all the paramenters entered to vm
 * (from cli using flags)
 */
{
  try{
    ////////// Output File parameter(files section) //////////
    
    // if there is a output paramenter assign to output attribute, 
    // otherwise assign the default value
    output = vm["output"].as<string>();
    if(output == "")
      throw Exception("No output file supplied!");

    // if there is a output paramenter assign to output attribute, 
    // otherwise assign the default value
    input = vm["input"].as<string>();

    
    ////////// print parameters(print section) //////////
    
    // if there is a quiet paramenter assign to quiet attribute, otherwise assign the default value
    quiet = vm["quiet"].as<bool>();

    // if there is a show paramenter assign to show attribute, otherwise assign the default value
    show = vm["show"].as<bool>();

    // if there is a pretty paramenter assign to pretty attribute, otherwise assign the default value
    pretty = vm["pretty"].as<bool>();

    ////////// mask parameters (mask section) //////////
    //length
    minlength = vm["minlength"].as<unsigned int>();
    maxlength = vm["maxlength"].as<int>();

 
    if(minlength >0 && maxlength == 0)
      maxlength = -1; //there isn't a maximum length
    else if (minlength > 0 && maxlength != 0)
    {
      if(maxlength < 0)
          maxlength = -1;
      else
       {
         if((int)minlength > maxlength)
          throw Exception("Invalid arguments(mask length).");
       }
    }
    else if (minlength == 0 && maxlength != 0)
    {
      if(maxlength < 0)
        maxlength = -1; //there isn't a maximum length
    } // else case is when minlength == 0 and maxlength == 0
  

  
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


    if(minlower >0 && maxlower == 0)
      maxlower = -1; //there isn't a maximum lowercases
    else if (minlower > 0 && maxlower != 0)
    {
      if(maxlower < 0)
        maxlower = -1; //there isn't a maximum lowercase
      else
      {
        if((int)minlower > maxlower)
        throw Exception("Invalid arguments(mask lower cases).");
      }
    }
    else if (minlower == 0 && maxlower != 0)
    {
      if(maxlower < 0)
        maxlower = -1; //there isn't a maximum lowercases
    }// else case is when minlower == 0 and maxlower == 0

    // upper characters
    minupper = vm["minupper"].as<unsigned int>();
    maxupper = vm["maxupper"].as<int>();

    if(minupper >0 && maxupper == 0)
      maxupper = -1; //there isn't a maximum uppercases
    else if (minupper > 0 && maxupper != 0)
    {
      if(maxupper < 0)
        maxupper = -1; //there isn't a maximum uppercases
      else
      {
        if((int)minupper > maxupper)
        throw Exception("Invalid arguments(mask uppercases).");
      }
    }
    else if (minupper == 0 && maxupper != 0)
    {
      if(maxupper < 0)
        maxupper = -1; //there isn't a maximum uppercases
    }// else case is when minupper == 0 and maxupper == 0


    // digit characters
    mindigit = vm["mindigit"].as<unsigned int>();
    maxdigit = vm["maxdigit"].as<int>();


    if(mindigit >0 && maxdigit == 0)
      maxdigit = -1; //there isn't a maximum digits
    else if (mindigit > 0 && maxdigit != 0)
    {
      if(maxdigit < 0)
        maxdigit = -1; //there isn't a maximum digits
      else
      {
        if((int)mindigit > maxdigit)
          throw Exception("Invalid arguments(mask digits).");
      }
    }
    else if (mindigit == 0 && maxdigit != 0)
    {
      if(maxdigit < 0)
        maxdigit = -1; //there isn't a maximum digits
    }// else case is when mindigit == 0 and maxdigit == 0

    // special characters
    minspecial = vm["minspecial"].as<unsigned int>();
    maxspecial = vm["maxspecial"].as<int>();

    if(minspecial >0 && maxspecial == 0)
      maxspecial = -1; //there isn't a maximum special  characters
    else if (minspecial > 0 && maxspecial != 0)
    {
      if(maxspecial < 0)
        maxspecial = -1; //there isn't a maximum special characters
      else
      {
        if((int)minspecial > maxspecial)
        throw Exception("Invalid arguments(mask special characters).");
      }
    }
    else if (minspecial == 0 && maxspecial != 0)
    {
      if(maxspecial < 0)
        maxspecial = -1; //there isn't a maximum special characters
    }// else case is when minspecial == 0 and maxspecial == 0
  
    ////////// parallel parameters (parallel section) //////////
    // threads = vm["threads"].as<unsigned int>();
    // int maxthreads = omp_get_max_threads();
    // if((int)threads > maxthreads)
    //   throw Exception("You haven't enough threads(max threads: " + to_string(maxthreads) + ")");
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    cout << policygen << endl;
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

    //parallel section
  cout << "\n--- parallel section --" << endl;
  cout << "threads: " << threads << endl;
}