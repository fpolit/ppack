#include "../../include/args.hpp"

//////////////////////////////////
///// mstruct implementation /////
//////////////////////////////////

Margs::Margs(unsigned int min_length, int max_length,             //
             unsigned int min_complexity, int max_complexity,     // mask struct parameters
             unsigned int min_occurrence, int max_occurrence,       //
             bool quiet_print, bool show_masks,                   // print parametersxs
             vector<string> scharsets, vector<string> acharsets,
             vector<Mask> check_masks,string check_mask_file,
             string output_file, string statsgen_output)
  :Args(min_length, max_length,
        quiet_print,
        output_file, statsgen_output)
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

Margs::Margs(po::variables_map vm, po::options_description maskgen)
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
  }
  catch(std::exception &error)
  {
    cout << error.what() << endl;
    cout << maskgen << endl;
    exit(EXIT_FAILURE);
  }
}

void Margs::debug()
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
