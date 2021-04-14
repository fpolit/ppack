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
