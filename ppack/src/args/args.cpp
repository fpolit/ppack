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


#include "../include/args.hpp"
//#include "../include/exceptions/args.hpp"


//////////////////////////////////
///// rstruct implementation /////
//////////////////////////////////

Args::Args(unsigned int min_length, int max_length,
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

void Args::debug()
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
