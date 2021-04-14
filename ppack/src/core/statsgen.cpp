#include "../../include/core/statsgen.hpp"

// statgen stats struct (property , occurence)
typedef struct statstruct
{
  unsigned long total=0; //total number of analyzed passwords
  map<SCS, int> scs;
  map<Mask, int> mask;
  map<unsigned int, int> length;
}statstruct;

/*-------------------------------*/


bool sfilter(Password passwd, sstruct pargs)
{
  // add more complx filter
  unsigned acsSize = pargs.acs.size();
  unsigned scsSize = pargs.scs.size();

  if(acsSize > 0 ||  scsSize > 0)
  {
    if(acsSize > 0 && scsSize == 0)
    {
      if(Password::checkLength(passwd, pargs.minlength, pargs.maxlength) &&
          Password::checkACS(passwd, pargs.acs))
          return true;
      return false;
    }
    else if(scsSize > 0 && acsSize == 0)
    {
      if(Password::checkLength(passwd, pargs.minlength, pargs.maxlength) &&
          Password::checkSCS(passwd, pargs.scs))
          return true;
      return false;
    }
    else //scsSize > 0 AND acsSize > 0
    {
      if(Password::checkLength(passwd, pargs.minlength, pargs.maxlength) &&
          Password::checkSCS(passwd, pargs.scs) &&
          Password::checkACS(passwd, pargs.acs))
          return true;
      return false;
    }
  }
  else
  {
    if(Password::checkLength(passwd, pargs.minlength, pargs.maxlength))
      return true;
    return false;
  }
}

vector<Password> passwdBlock(ifstream *wordlist, int block,
                              sstruct pargs, unsigned long* totalPasswd)
{
  string passwd;
  vector<Password> vpasswd;
  while((getline(*wordlist, passwd) && passwd!="") && vpasswd.size() <= block)
    {
      Password password(passwd);
      *totalPasswd += 1;
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
  unsigned long totalPasswd = 0; //total number of analyzed password

  try{
    while(wordlist->is_open()) // ensure that you close the wordlist when it hasn't more password
    {
      //this function read at most 'block' filtered passwords.
      vector<Password> vpasswd = passwdBlock(wordlist, block, pargs, &totalPasswd);

#pragma omp parallel for shared(vpasswd, stats) num_threads(1)
      for(int k=0; k<vpasswd.size(); k++)
        {
          Password passwd = vpasswd.at(k);
          //cout << "Thread " << omp_get_thread_num() << " Processing " << passwd << endl;

          //length password stats
          int passwdSize = passwd.size();
          if(stats.length.find(passwdSize) != stats.length.end())
            {
              #pragma omp atomic update
              stats.length[passwdSize] += 1;
            }
          else
            {
              #pragma omp atomic write
              stats.length[passwdSize] = 1;
            }

          // Character set stats
          SCS passwdSCS = passwd.getSCS();
          if(stats.scs.find(passwdSCS) != stats.scs.end())
            {
              #pragma omp atomic update
              stats.scs[passwdSCS] += 1;
            }
          else
            {
              #pragma omp atomic write
              stats.scs[passwdSCS] = 1;
            }


          // advance mask stats
          Mask passwdMask = passwd.getMask();
          if(stats.mask.find(passwdMask) != stats.mask.end())
            {
              #pragma omp atomic update
              stats.mask[passwdMask] += 1;
            }
          else
            {
              #pragma omp atomic write
              stats.mask[passwdMask] = 1;
            }
        }
    }
    stats.total = totalPasswd;
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

void writeStatsgen(statstruct stats, sstruct pargs)
{
  if(!pargs.quiet)
    cout << Logo::randomLogo() << endl;

  bool prettyOutput = pargs.pretty;
  if(prettyOutput)
  {
    FinePrint::status("Analyzing passwords in [" + pargs.wordlist + "]");
    FinePrint::status("Using " + to_string(pargs.threads) + " threads.");
    FinePrint::empty();
  }
  else
    {
      cout << "[*] Analyzing passwords in [" + pargs.wordlist + "]" << endl;
      cout << "[*] Using " << pargs.threads << " threads." << endl;
    }

  unsigned long total = stats.total;

  cout.setf(ios::fixed); // fix the number of decimal to print
  cout.setf(ios::showpoint);
  cout<<setprecision(1);

  if(prettyOutput)
    FinePrint::status("Length:");
  else
    cout << "[*] Length:" << endl;
  if(pargs.hiderare > 0)
  {
    double minpercent = pargs.hiderare/100;
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

    ofstream statsgenOutput;
    if(pargs.output != "")
    {
      statsgenOutput.open(pargs.output);

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
        statsgenOutput << mask << " , " << occurence << endl;
      }
      if(pargs.pretty)
        FinePrint::successful("Writing masks in [" + pargs.output +"]");
      else
        cout << "[*] Writing masks in [" << pargs.output << "]" << endl;
    }
    else
    {
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

    ofstream statsgenOutput;
    if(pargs.output != "")
    {
      statsgenOutput.open(pargs.output);

      for(auto [mask, occurence]: stats.mask)
      {
        double percent = (double)occurence/total;

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
        statsgenOutput << mask << " , " << occurence << endl;
      }
      if(pargs.pretty)
        FinePrint::successful("Writing masks in [" + pargs.output +"]");
      else
        cout << "[+] Writing masks in [" << pargs.output  << "]" << endl;
    }
    else
    {
      for(auto [mask, occurence]: stats.mask)
      {
        double percent = (double)occurence/total;
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

    // for(auto [mask, occurence]: stats.mask)
    // {
    //   double percent = (double)occurence/total;
    //   if(prettyOutput)
    //     cout  << FinePrint::greenText("[+]")
    //           << setw(32) << mask << " : "
    //           << setw(5)  << formatPercent(percent) << "%"
    //           << " (" << occurence << ")" << endl;
    //   else
    //    cout  << "[+]"
    //           << setw(32) << mask << " : "
    //           << setw(5)  << formatPercent(percent) << "%"
    //           << " (" << occurence << ")" << endl;;
    // }
  }
  if(prettyOutput)
  {
    FinePrint::empty();
    FinePrint::successful("Analized 100% (" + to_string(total) +")");
  }
  else
    cout << "Analized 100% (" + to_string(total) +")" << endl;
}
