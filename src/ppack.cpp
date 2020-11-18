/*
 * Implementation of ppack class
 * statsgen method: Compute statistis of a wordlist
 *
 * policygen method: generate a set of mask with some rules
 */

#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include<iostream>
#endif //__INCLUDE_STD_IOSTREAM_H_

#ifndef __INCLUDE_FSTREAM_H__
#define __INCLUDE_FSTREAM_H__
#include<fstream>
#endif //__INCLUDE_FSTREAM_H__

// #ifndef __INCLUDE_STD_STRING_H_
// #define __INCLUDE_STD_STRING_H_
// #include<string>
// #endif //__INCLUDE_STD_STRING_H_

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif // __INCLUDE_STD_VECTOR_H__

using namespace std;

#ifndef __INCLUDE_MASK_H_
#define __INCLUDE_MASK_H_
#include "../include/mask.hpp"
#endif //__INCLUDE_MASK_H_

#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../include/ppack.hpp"
#endif //__INCLUDE_PPACK_H__


#ifndef __INCLUDE_LOGOS_H__
#define __INCLUDE_LOGOS_H__
#include "../include/logos.hpp"
#endif //__INCLUDE_LOGOS_H__


#ifndef __INCLUDE_COLOR_H__
#define __INCLUDE_COLOR_H__
#include "../include/color.hpp"
#endif //__INCLUDE_COLOR_H__


#ifndef __INCLUDE_CSV_H__
#define __INCLUDE_CSV_H__
#include "../include/csv.hpp"
#endif //__INCLUDE_CSV_H__



////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Statsgen implementation  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

vector<Password>* passwdBlock(ifstream wordlist, int BLOCK)
{
  string passwd;
  vector<Password> *vpasswd = new vector<Password>;
  while((getline(wordlist, passwd) && passwd!="") && vpasswd->size() <= BLOCK)
    {
      vpasswd->push_back(passwd);
    }

  if(getline(wordlist, passwd) && passwd!="")
    wordlist.close(); //closing wordlist file because it hasn't more passwords

  return vpasswd;
}


void statsgen(string wordlist, string output,                           //IO parameters
              bool hiderare, bool quiet,                      //print parameters
              vector<string> charset,                            //password charset
              int minlength, int maxlength)                         //length parameters
{
  ifstream wordlist_file(wordlist);
  //string passwd;
  int block_passwds=1000; // max block of pasword that i will read from wordlists
  statstruct sstruct; //stats struct

  while(wordlist_file.is_open()) // ensure that you close the wordlist when it hasn't more password
    {
      vector<Password> *vpasswd = passwdBlock(wordlist_file, block_passwds); // this function read at most 1000 passwords

#pragma omp parallel for shared(vpasswd, sstruct)
      for(int k=0; k<vpasswd->size(); k++)
        {
          Password passwd = vpasswd->at(k);

          //length password stats
          if(sstruct.length.find(passwd.size()) != sstruct.length.end())
            {
              #pragma omp critical
              sstruct.length[passwd.size()] = 1;
            }
          else
            {
              #pragma omp atomic
              sstruct.length[passwd.size()] += 1;
            }

          // Character set stats
          if(sstruct.scs.find(passwd.scs()) != sstruct.scs.end())
            {
              #pragma omp critical
              sstruct.scs[passwd.scs()] = 1;
            }
          else
            {
              #pragma omp atomic
              sstruct.scs[passwd.scs()] += 1;
            }


          // advance mask stats
          if(sstruct.mask.find(passwd.getMask()) != sstruct.mask.end())
            {
              #pragma omp critical
              sstruct.mask[passwd.getMask()] = 1;
            }
          else{
            #pragma omp atomic
            sstruct.mask[passwd.getMask()] += 1;
          }

        }

      // free vpasswd vector to read the other block of passwds
      delete [] vpasswd;
    }
}

void statsgen_results(statstruct sstruct)
{
  // using sstuct struct write the output file and show the generated stats
}


////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// maskgen implementation   /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


bool checkOccurence(int occurence, int minoccurence, int maxoccurence)
{
  if(occurence > minoccurence && occurence < maxoccurence)
    return true;
  return false;
}

bool satisfyFilter(Mask mask, int occurence, maskgenStruct mskgn)
{
  //Mask mask(mask_str);
  if(checkLength(mask, mskgn.minlength, mskgn.maxlength) &&
     //checkChartset(mask, mskgn.charsets) &&
     checkOcurrence(occurence, mskgn.minoccurence, mskgn.maxoccurence) &&
     checkComplexity(mask, mskgn,mincompexity, mskgn.maxcomplexity))
    return true;
  return false;
}

void maskgen(string statsgen_output, string output,    //IO parameters
             bool show, bool quiet,                           //print parameters
             vector<Mask> checkmasks,string checkmasksfile,       //checkmask parameters
             vector<string> charset,                            //password charset
             int minlength, int maxlength,                         //length parameters
             int mincomplexity, int maxcomplexity,                 //complexity parameters
             int minoccurrence, int maxoccurrence)                 //occurrence parameters
{
  CSVReader statsgen(statsgen_output);

  maskgenStruct mskgn = init_maskgen_struct(minlength, maxlength,
                                            mincomplexity, maxcomplexity,
                                            minoccurrence, maxoccurrence,
                                            charset);

  // mask and occurence map
  map<Mask, int> fmasks; //filtered masks (mask, occurence of mask)
  vector<vector<string>> results = statsgen.getData(); //result of statsgen
#pragma omp parallel for shared(statsgen_results)
  for(int k=0; k < results.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      Mask mask(results[k][0]);
      int occurence = stoi(results[k][1]); //convert from string to interger

      if(satisfyFilter(mask, occurence, mskgn))
        {
          fmasks[mask] = occurence;
        }
    }

  if(!quiet)
    {
      string ppack_logo = Logo::random();
      cout << ppack_logo << endl;
    }

  ofstream maskgen_output(output);
  maskgen_output.open();

  if(show)
    {
      for(auto const& [mask, occurence] : fmasks)
        {
          maskgen_output << mask << endl;
        }
    }
  else
    {
      for(auto const& [mask, occurence] : fmasks)
        {
          maskgen_output << mask << endl;
          // print the mask and its occurence
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Policygen implementation /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


poliStruct init_polistruct(int minlength, int maxlength,                         //length parameters
                     int minlower, int maxlower,                           //
                     int minupper, int maxupper,                           // password
                     int mindigit, int maxdigit,                           // charset
                     int minspecial, int maxspecial)
{
  poliStruct pstruct;
  pstruct.minlength = minlength;
  pstruct.maxlength = maxlength;
  pstruct.minlower = minlower;
  pstruct.maxlower = maxlower;
  pstruct.minupper = minupper;
  pstruct.maxupper = maxupper;
  pstruct.mindigit = mindigit;
  pstruct.maxdigit = maxdigit;
  pstruct.minspecial = minspecial;
  pstruct.maxspecial = maxspecial;

  return pstruct;
}


string repeat(string str, int n)
{
  string repeat_str="";
  for(int k=0; k<n; k++)
    repeat_str += str;

  return repeat_str;
}




Base::Base(poliStruct init)
{
  bstruct = init;
  string init_mask;

  init_mask = repeat("?l", bstruct.minlower) +\
    repeat("?d", bstruct.minupper) +\
    repeat("?u", bstruct.minupper) +\
    repeat("?s", bstruct.minspecial);

  Mask initMask(init_mask);

  base = new vector<Mask>;
  base->push_back(initMask);
  length = 1;
}

Base::~Base()
{
  delete [] base;
}

void Base::appendMask(Mask step)
{
  base->push_back(step);
}

void Base::maskStep()
{
  vector<Mask> *step_base = new vector<Mask>;
  for(Mask mask : *base)
    {
      maskStruct mstruct = maskAnalysis(mask);

      if(mstruct.lowercase <= bstruct.maxlower)
        {
          step_base->push_back(mask + "?l");
          if(mstruct.digit <= bstruct.maxdigit)
              step_base->push_back(mask + "?d");

          if(mstruct.uppercase <= bstruct.maxupper)
              step_base->push_back(mask + "?u");

          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.digit <= bstruct.maxdigit)
        {
          step_base->push_back(mask + "?d");
          if(mstruct.uppercase <= bstruct.maxupper)
              step_base->push_back(mask + "u");
          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.uppercase <= bstruct.maxupper)
        {
          step_base->push_back(mask + "?u");
          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.special <= bstruct.maxspecial)
        {
          step_base->push_back(mask + "?s");
        }
    }

  // replace the updated base(step_base) with base
  delete [] base; // fre memory of base = vector<Mask>
  base = step_base;
  step_base = nullptr;
  length += 1;
}

void permuteMasks(Base base)
/*
 * This function compute all the permutations without repetitions
 * and write all of them to a file.
 */
{
  cout << "search for a c++ function to do this work(permutations)" << endl;
}

void corePolicygen(poliStruct init)
{
  Base base(init);

  for(int len=base.getLength(); len < base.getPoliMinLength(); len++)
    {
      // generate all the posible mask with the required parameter
      // and increase the length of base in one
      base.maskStep();
    }

  // now the length of base is equal to minlength(policygen paramemter)
  for(int len=base.getLength(); len < base.getPoliMaxLength(); len++)
    {
      permuteMasks(base); // compute all the permutation of the mask(without repetitions)
      base.maskStep();
    }
}

static void policygen(string output,                       //Output File
                      bool quiet, bool show,                           //print parameters
                      int minlength, int maxlength,                         //length parameters
                      int minlower, int maxlower,                           //
                      int minupper, int maxupper,                           // password
                      int mindigit, int maxdigit,                           // charset
                      int minspecial, int maxspecial)
{
  poliStruct pstruct =  init_polistruct(minlength, maxlength,
                                      minlower, maxlower,
                                      minupper, maxupper,
                                      mindigit, maxdigit,
                                      minspecial, maxspecial);

  corePolicygen(pstruct); //do almost all the work()

  if(quiet == false) // print the ppack logo
    {
      string ppack_logo = Logo::random();
      cout << ppack_logo << endl;
    }
  print_status("Saving generated masks to [" + output +".hcmask]");
  print_status("Using 8 OMP Threads.");

  // string password_policy =
  //   "Password policy:"  +\
  //   "\n\tPass Lengths:" + " min: " + minlength + " max: " + maxlength + \
  //   "\n\tMin strength:" + " l:" + minlower + " u:" + minupper + " d:" + mindigit + " s:" + minspecial +\
  //   "\n\tMin strength:" + " l:" + minlower + " u:" + minupper + " d:" + mindigit + " s:" + minspecial + "\n";

  //print_status("Policy Masks: ");

  if(show==true)
    {
      cout << "show generated masks" << endl;
    }

  print_status("Policy Masks: ");
}
