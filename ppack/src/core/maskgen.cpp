#include "../../include/core/maskgen.hpp"

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

// MOVE TO ppack/include/exceptions - date Apr 14 2021
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
    FinePrint::status("Using " + to_string(pargs.threads) + " threads.");
    FinePrint::empty();
  }
  else
  {
    cout << "[*] Analyzing masks in [" + pargs.statsgen + "]" << endl;
    cout << "[*] Using " << pargs.threads << " threads." << endl;
  }

  int generatedMasks=0;
  if(pargs.output != "" && !pargs.show)
  {
    maskgenOutput = new ofstream(pargs.output);

    int k;
#pragma omp parallel for default(none) \
      shared(statsgenResults, maskgenOutput, generatedMasks, pargs) private(k)
    for(k=0; k < statsgenResults.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      vector<string> kresult = statsgenResults[k];
      Mask mask(kresult[0]);
      int occurence = stoi(kresult[1]); //convert from string to interger

      //cout << "thread " << omp_get_thread_num() << " process " << mask << " mask." << endl;

      if(mFilter(mask, occurence, pargs))
      {
        #pragma omp critical
          *maskgenOutput << mask << endl;

        #pragma omp atomic update
          generatedMasks += 1;
      }
    }
    maskgenOutput->close();

    if(prettyOutput)
    {
      FinePrint::empty();
      FinePrint::status("Finished generating masks:");
      cout << "\t" << "Masks generated: " << generatedMasks << endl;
      FinePrint::successful("Mask wrote in [" +  pargs.output + "]");
    }
    else
    {
      cout << "\nFinished generating masks:" << endl;
      cout << "\t" << "Masks generated: " << generatedMasks << endl;
      cout << "[+] Mask wrote in [" +  pargs.output + "]" << endl;
    }
  }
  else if(pargs.output != "" && pargs.show)
  {
    maskgenOutput = new ofstream(pargs.output);
    cout  << "[" << setw(3) << "L:" << "]" << setw(32) << std::left <<  " Mask:"
          << "[" << setw(6) << "Occ:" << "]" << endl;

    int k;
#pragma omp parallel for \
      shared(statsgenResults, maskgenOutput, generatedMasks, pargs) private(k)
    for(k=0; k < statsgenResults.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      vector<string> kresult = statsgenResults[k];
      Mask mask(kresult[0]);
      int occurence = stoi(kresult[1]); //convert from string to interger

      if(mFilter(mask, occurence, pargs))
        {
          #pragma omp critical
          {
            *maskgenOutput << mask << endl;
            cout  << "[ " << setw(3) << std::left << mask.length() << "] " << setw(32) <<  mask
                  << "[ " << setw(6) << occurence << "]" << endl;
          }
          #pragma omp atomic update
            generatedMasks += 1;

        }
    }
    maskgenOutput->close();

    if(prettyOutput)
    {
      FinePrint::empty();
      FinePrint::status("Finished generating masks:");
      cout << "\t" << "Masks generated: " << generatedMasks << endl;
      FinePrint::successful("Mask wrote in [" +  pargs.output + "]");
    }
    else
    {
      cout << "\nFinished generating masks:" << endl;
      cout << "\t" << "Masks generated: " << generatedMasks << endl;
      cout << "[+] Mask wrote in [" +  pargs.output + "]" << endl;
    }
  }
  else if(pargs.show && pargs.output == "")
  {
    cout  << "[" << setw(3) << "L:" << "]" << setw(32) << std::left <<  " Mask:"
          << "[" << setw(6) << "Occ:" << "]" << endl;

  int k;
#pragma omp parallel for \
      shared(statsgenResults, maskgenOutput, generatedMasks, pargs) private(k)
    for(k=0; k < statsgenResults.size(); k++)
    {
      // first element in statsgen output is mask and
      // second element is occurence of the mask(first element)
      vector<string> kresult = statsgenResults[k];
      Mask mask(kresult[0]);
      int occurence = stoi(kresult[1]); //convert from string to interger

      if(mFilter(mask, occurence, pargs))
      {
        #pragma omp critical
        {
          cout  << "[ " << setw(3) << std::left << mask.length() << "] " << setw(32) <<  mask
              << "[ " << setw(6) << occurence << "]" << endl;
        }

        #pragma omp atomic update
          generatedMasks += 1;
      }
    }
    if(prettyOutput)
    {
      FinePrint::empty();
      FinePrint::status("Finished generating masks:");
      cout << "\t" << "Masks generated: " << generatedMasks << endl;
    }
    else
    {
      cout << "\nFinished generating masks:" << endl;
      cout << "\t" << "Masks generated: " << generatedMasks << endl;
    }
  }
  else  //no output and show flags supplied
    throw invalid_options;
}
