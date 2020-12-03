  /*
 * Implementation of ppack class - 23 nov 2020
 * statsgen method:  Compute statistis of a wordlist
 * maskgen methos:   Generate mask from the statistics generated by statsgen
 * policygen method: Generate a set of mask with some requirements
 *
 * Reimplementation PPACK class - 25 nov 2020
 * COMPLETED: (27 nov 2020)
 * The base class is defined in include/basepoli.hpp
 * and implemented in src/basepoli.cpp
 * --- Separate Base class of ppack.hhp in its own head file and its implementation file ---
 *  
 *
 *
 * NO COMPLETED
 * --- Use pstruct class to manage the parameter of statsgen, maskgen and policygen ---
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
*/



#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../include/ppack.hpp"
#include <exception>
#include <fstream>
#endif //__INCLUDE_PPACK_H__


//////////////////////////////////////////////
////////// statsgen  implementation   ////////
//////////////////////////////////////////////

bool sfilter(Password passwd, sstruct pargs)
{
  // add more complx filter
  if(Password::checkLength(passwd, pargs.minlength, pargs.maxlength))
    return true;
  return false;
}

vector<Password> passwdBlock(ifstream *wordlist, int block, 
                              sstruct pargs, unsigned long* passwdCounter)
{
  string passwd;
  vector<Password> vpasswd;
  while((getline(*wordlist, passwd) && passwd!="") && vpasswd.size() <= block)
    {
      Password password(passwd);
      *passwdCounter += 1;
      if(sfilter(passwd,  pargs))
        vpasswd.push_back(password);
    }

  getline(*wordlist, passwd);
  if(passwd=="")
    wordlist->close(); //closing wordlist file because it hasn't more passwords

  return vpasswd;
}

statstruct coreStatsgen(sstruct pargs)
{
  ifstream *wordlist  = new ifstream(pargs.wordlist);
  int block = 1000; // max block of pasword to read from wordlists
  statstruct stats; //stats of wordlists
  unsigned long passwdCounter = 0; //total number of analyzed password 
  
  try{
    while(wordlist->is_open()) // ensure that you close the wordlist when it hasn't more password
    {
      //this function read at most 'block' filtered passwords. 
      vector<Password> vpasswd = passwdBlock(wordlist, block, pargs, &passwdCounter); 

      //#pragma omp parallel for shared(vpasswd, stats)
      for(int k=0; k<vpasswd.size(); k++)
        {
          Password passwd = vpasswd.at(k);

          //length password stats
          int passwdSize = passwd.size();
          if(stats.length.find(passwdSize) != stats.length.end())
            {
              //#pragma omp atomic
              stats.length[passwdSize] += 1;
            }
          else
            {
              //#pragma omp critical
              stats.length[passwdSize] = 1;
            }

          // Character set stats
          SCS passwdSCS = passwd.getSCS();
          if(stats.scs.find(passwdSCS) != stats.scs.end())
            {
              //#pragma omp atomic
              stats.scs[passwdSCS] += 1;
            }
          else
            {
              //#pragma omp critical
              stats.scs[passwdSCS] = 1;
            }


          // advance mask stats
          Mask passwdMask = passwd.getMask();
          if(stats.mask.find(passwdMask) != stats.mask.end())
            {
              //#pragma omp atomic
              stats.mask[passwdMask] += 1;
            }
          else
            {
              //#pragma omp critical
              stats.mask[passwdMask] = 1;
            }
        }
    }
    stats.total = passwdCounter;
    return stats;
  }
  catch (std::exception& error)
  {
    cerr << error.what() << endl;
    wordlist->close();
    exit(EXIT_FAILURE);
  }
}

double formatPercent(double decimalPercent)
{
  double percent = decimalPercent*100;
  return  percent;
}

void printStatsgen(statstruct stats, sstruct pargs)
{
  if(!pargs.quiet)
    cout << Logo::randomLogo() << endl;

  bool prettyOutput = pargs.pretty;
  if(prettyOutput)
  {
    FinePrint::status("Analyzing passwords in [" + pargs.wordlist + "]");
    FinePrint::empty();
  }
  else
    cout << "Analyzing passwords in [" + pargs.wordlist + "]" << endl;
  
  unsigned long total = stats.total;

  cout.setf(ios::fixed); // fix the number of decimal to print
  cout.setf(ios::showpoint);
  cout<<setprecision(1);

  if(prettyOutput)
    FinePrint::status("Length:");
  else
    cout << "[*] Length:" << endl;
  if(pargs.hiderare)
  {
    double minpercent = 0.01;
    for(auto [length, occurence]: stats.length)
    {
      double percent = (double)occurence/total;
      if(percent > minpercent)
      {
        if(prettyOutput)
          cout  << FinePrint::greenText("[+]")
              << setw(32) << length << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;
        else
         cout  << "[+]"
              << setw(32) << length << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;;
      }
    }
    if(prettyOutput)
      FinePrint::status("Simple charset:");
    else
      cout << "[*] Simple charset:" << endl;
    
    for(auto [scs, occurence]: stats.scs)
    {
      double percent = (double)occurence/total;
      if(percent > minpercent)
      {
        if(prettyOutput)
          cout  << FinePrint::greenText("[+]")
              << setw(32) << Mask::scstoString(scs) << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;
        else
         cout  << "[+]"
              << setw(32) << Mask::scstoString(scs) << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;;
      }
  }
    if(prettyOutput)
      FinePrint::status("Masks:");
    else
      cout << "Masks:" << endl;
    
    for(auto [mask, occurence]: stats.mask)
    {
      double percent = (double)occurence/total;
      if(percent > minpercent)
      {
        if(prettyOutput)
          cout  << FinePrint::greenText("[+]")
                << setw(32) << mask << " : "
                << setw(5)  <<  formatPercent(percent) << "%"
                << " (" << occurence << ")" << endl;
        else
          cout  << "[+]"
                << setw(32) << mask << " : "
                << setw(5)  <<  formatPercent(percent) << "%"
                << " (" << occurence << ")" << endl;;
      }
    }
  }
  else
  {
    for(auto [length, occurence]: stats.length)
    {
      double percent = (double)occurence/total;
      if(prettyOutput)
        cout  << FinePrint::greenText("[+]")
              << setw(32) << length << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;
      else
        cout  << "[+]"
              << setw(32) << length << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;;
    }
    if(prettyOutput)
      FinePrint::status("Simple charset:");
    else
      cout << "[*] Simple charset:" << endl;
    
    for(auto [scs, occurence]: stats.scs)
    {
      double percent = (double)occurence/total;
      if(prettyOutput)
        cout  << FinePrint::greenText("[+]")
              << setw(32) << Mask::scstoString(scs) << " : "
              << setw(5)  <<  formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;
      else
       cout  << "[+]"
            << setw(32) << Mask::scstoString(scs) << " : "
            << setw(5)  <<  formatPercent(percent) << "%"
            << " (" << occurence << ")" << endl;;
    }

    if(prettyOutput)
      FinePrint::status("Masks:");
    else
      cout << "Masks:" << endl;
    
    for(auto [mask, occurence]: stats.mask)
    {
      double percent = (double)occurence/total;
      if(prettyOutput)
        cout  << FinePrint::greenText("[+]")
              << setw(32) << mask << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;
      else
       cout  << "[+]"
              << setw(32) << mask << " : "
              << setw(5)  << formatPercent(percent) << "%"
              << " (" << occurence << ")" << endl;;
    }
  }
  if(prettyOutput)
  {
    FinePrint::empty();
    FinePrint::successful("Analized 100% (" + to_string(total) +")");
  }
  else
    cout << "Analized 100% (" + to_string(total) +")" << endl;
}

void PPACK::statsgen(sstruct pargs)
{
  statstruct stats = coreStatsgen(pargs);

  // print to console the computed stats
  printStatsgen(stats, pargs);
  if(pargs.output != "")
  {
    ofstream statsgenOutput;
    statsgenOutput.open(pargs.output);
    for(auto [mask, occurence]: stats.mask)
    {
      statsgenOutput << mask << " , " << occurence << endl;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// maskgen implementation   /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////


bool checkOccurrence(unsigned int maskOccurrence, unsigned int minoccurence, int maxoccurence)
{
  if(maxoccurence != -1)
  {
    if(maskOccurrence >= minoccurence && maskOccurrence <= maxoccurence)
    return true;
  }
  else
  {
    if(maskOccurrence >= minoccurence)
    return true;
  }
  return false;
}

bool mFilter(Mask mask, unsigned int occurrence, mstruct pargs)
{
  //Mask mask(mask_str);
  if(Mask::checkLength(mask, pargs.minlength, pargs.maxlength) &&
     //checkChartset(mask, mskgn.charsets) &&
     checkOccurrence(occurrence, pargs.minoccurrence, pargs.maxoccurrence) &&
     Mask::checkComplexity(mask, pargs.mincomplexity, pargs.maxcomplexity))
    return true;
  return false;
}


class invalid_options: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Invalid options(no show or output options supplied)";
  }
} invalid_options;

void coreMaskgen(ofstream *maskgenOutput, vector<vector<string>> statsgenResults, mstruct pargs)
/*
 * first element in statsgenResults is mask and
 * second element is occurence of the mask(first element)
*/
{
  bool prettyOutput = pargs.pretty;

  if(prettyOutput)
  {
    FinePrint::status("Analyzing masks in [" + pargs.statsgen + "]");
    FinePrint::empty();
  }
  else
  {
    cout << "[*] Analyzing masks in [" + pargs.statsgen + "]" << endl;
  }
  
  if(pargs.output != "" && !pargs.show)
  {
    maskgenOutput = new ofstream(pargs.output);
    for(int k=0; k < statsgenResults.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      Mask mask(statsgenResults[k][0]);
      int occurence = stoi(statsgenResults[k][1]); //convert from string to interger

      if(mFilter(mask, occurence, pargs))
        *maskgenOutput << mask << endl;
    }
    maskgenOutput->close();
    
    if(prettyOutput)
    {
      FinePrint::empty();
      FinePrint::status("Finished generating masks:");
      cout << "\t" << "Masks generated(UPDATE COUNTER): " << statsgenResults.size() << endl; 
      FinePrint::successful("Mask wrote in " +  pargs.output);
    }
    else
    {
      cout << "\nFinished generating masks:" << endl;
      cout << "\t" << "Masks generated(UPDATE COUNTER): " << statsgenResults.size() << endl; 
      cout << "[+] Mask wrote in " +  pargs.output << endl;
    } 
  }
  else if(pargs.output != "" && pargs.show)
  {
    maskgenOutput = new ofstream(pargs.output);
    cout  << "[" << setw(3) << "L:" << "]" << setw(32) << std::left <<  " Mask:"
          << "[" << setw(6) << "Occ:" << "]" << endl;
    for(int k=0; k < statsgenResults.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      Mask mask(statsgenResults[k][0]);
      int occurence = stoi(statsgenResults[k][1]); //convert from string to interger

      if(mFilter(mask, occurence, pargs))
        {
          *maskgenOutput << mask << endl;
          cout  << "[ " << setw(3) << std::left << mask.length() << "] " << setw(32) <<  mask
              << "[ " << setw(6) << occurence << "]" << endl;
        }
    }
    maskgenOutput->close();

    if(prettyOutput)
    {
      FinePrint::empty();
      FinePrint::status("Finished generating masks:");
      cout << "\t" << "Masks generated(UPDATE COUNTER): " << statsgenResults.size() << endl; 
      FinePrint::successful("Mask wrote in " +  pargs.output);
    }
    else
    {
      cout << "\nFinished generating masks:" << endl;
      cout << "\t" << "Masks generated(UPDATE COUNTER): " << statsgenResults.size() << endl; 
      cout << "[+] Mask wrote in " +  pargs.output << endl;
    } 
  }
  else if(pargs.show && pargs.output == "")
  {
    cout  << "[" << setw(3) << "L:" << "]" << setw(32) << std::left <<  " Mask:"
          << "[" << setw(6) << "Occ:" << "]" << endl;
    for(int k=0; k < statsgenResults.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      Mask mask(statsgenResults[k][0]);
      int occurence = stoi(statsgenResults[k][1]); //convert from string to interger

      if(mFilter(mask, occurence, pargs))
        cout  << "[ " << setw(3) << std::left << mask.length() << "] " << setw(32) <<  mask
              << "[ " << setw(6) << occurence << "]" << endl;
    }
    if(prettyOutput)
    {
      FinePrint::empty();
      FinePrint::status("Finished generating masks:");
      cout << "\t" << "Masks generated(UPDATE COUNTER): " << statsgenResults.size() << endl; 
    }
    else
    {
      cout << "\nFinished generating masks:" << endl;
      cout << "\t" << "Masks generated(UPDATE COUNTER): " << statsgenResults.size() << endl; 
    }  
  } else {
  throw invalid_options;
}
}
void PPACK::maskgen(mstruct pargs)
{
  CSVReader statsgen(pargs.statsgen);

  vector<vector<string>> results = statsgen.getData(); //results of statsgen

  if(!pargs.quiet)
    cout << Logo::randomLogo() << endl;
  
  ofstream *maskgenOutput;

  try 
  {
    coreMaskgen(maskgenOutput, results, pargs);
  }
  catch (std::exception& error) {
    cerr << error.what() << endl;
    //delete maskgenOutput;
    exit(EXIT_FAILURE);
  }
}

namespace ppack{
  string VERSION = "1.0";
  int release = 1;
}

//////////////////////////////////////////////
////////// policygen implementation   ////////
//////////////////////////////////////////////

void PPACK::policygen(pstruct pargs)
{
  if(pargs.quiet == false) // print the ppack logo
    cout << Logo::randomLogo() << endl;

  if(pargs.pretty)
  {
    FinePrint::status("Saving generated masks to [" + pargs.output + "]");
    //FinePrint::status("Using 8 OMP Threads.");
    FinePrint::status("Password policy:");
  }
  else {
    cout << "[*] Saving generated masks to [" + pargs.output + "]" << endl;
    cout << "[*] Password policy:" << endl;
  }
  cout << "\t" << "Password Lengths: "  << " min:" << setw(2) << pargs.minlength
                                        << " max:" << setw(2) << pargs.maxlength << endl;

  cout << "\t" << "Minimun strength: "  << " l:" << setw(3) << pargs.minlower
                                        << " u:" << setw(3) << pargs.minupper
                                        << " d:" << setw(3) << pargs.mindigit
                                        << " s:" << setw(3) << pargs.minspecial << endl;

  cout << "\t" << "Maximun strength: "  << " l:" << setw(3) << pargs.maxlower
                                        << " u:" << setw(3) << pargs.maxupper
                                        << " d:" << setw(3) << pargs.maxdigit
                                        << " s:" << setw(3) << pargs.maxspecial << endl;
  corePolicygen(pargs); //do almost all the work()
}
