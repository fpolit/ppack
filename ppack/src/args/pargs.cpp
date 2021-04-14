#include "../../include/args.hpp"

//////////////////////////////////
/////   Pargs implementation /////
//////////////////////////////////


Pargs::Pargs(unsigned int min_length, int max_length,    //
             unsigned int min_lower, int max_lower,      // masks
             unsigned int min_upper, int max_upper,      // struct
             unsigned int min_digit, int max_digit,      // parameters
             unsigned int min_special, int max_special,  //
             bool quiet_print, bool show_masks,          // print parameters
             string output_file, string input_file)      // io parameter
  :Args(min_length, max_length,
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

Pargs::Pargs(po::variables_map vm, po::options_description policygen)
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
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    cout << policygen << endl;
    exit(EXIT_FAILURE);
  }
}


void Pargs::debug() // show all the parameters
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
