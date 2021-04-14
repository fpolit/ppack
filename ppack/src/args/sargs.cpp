
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
