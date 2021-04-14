/*
 * Base class implementation - 25 nov 2020
 *
 *
 *
 * Depuration: 
 * TESTED ALL THE FUNCTION with exeption of permuteMasks,
 * because it isn't implemented yet.
 *
 *
 * No tested functions: ALL FUNCTION TESTED
 *
 * No implemented functions:
 *  void permuteMasks(Base base)
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 *
 */


//#include "ppack/base.py"
#include "../include/base.py"
string repeat(string str, int n); // helper function

Base::Base()
{
  length = 0;
}

Base::Base(baseStruct initial)
{
  bstruct = initial;
  string init_mask = "";
  init_mask += repeat("?l", bstruct.minlower);
  init_mask += repeat("?u", bstruct.minupper);
  init_mask += repeat("?s", bstruct.minspecial);
  init_mask += repeat("?d", bstruct.mindigit);

  Mask initMask(init_mask);
  baseMasks.push_back(initMask);
  length = initMask.length();
}


// tested 27 nov 2020
Base mask_step(Base init_base) // init base
{
  unsigned int length_gbase = init_base.get_length()+1;
  baseStep bstruct = base.get_base_struct();
  Base gbase = Base(bstruct, length_gbase); // generated base

  for(Mask mask : init_base.get_masks())
    {
      maskStruct mstruct = mask.get_mask_struct();

      if(mstruct.lowercase < bstruct.maxlower || bstruct.maxlower == -1)
        {
          gbase.append_mask(realloc_mask(mask, "?l"));
          if(mstruct.digit < bstruct.maxdigit || bstruct.maxdigit == -1)
              gbase.append_mask(realloc_mask(mask, "?d"));

          if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
              gbase.append_mask(realloc_mask(mask, "?u"));

          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            gbase.append_mask(realloc_mask(mask, "?s"));
        }
      else if(mstruct.digit < bstruct.maxdigit || bstruct.maxdigit == -1)
        {
          gbase.append_mask(realloc_mask(mask, "?d"));
          if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
              gbase.append_mask(realloc_mask(mask, "?u"));
          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            gbase.append_mask(realloc_mask(mask, "?s"));
        }
      else if(mstruct.uppercase < bstruct.maxupper || bstruct.maxupper == -1)
        {
          gbase.append_mask(realloc_mask(mask, "?u"));
          if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
            gbase.append_mask(realloc_mask(mask, "?s"));
        }
      else if(mstruct.special < bstruct.maxspecial || bstruct.maxspecial == -1)
        {
          gbase.append_mask(realloc_mask(mask, "?s"));
        }
    }

    return gbase;
}


void Base::append_mask(Mask step)
{
  masks.push_back(step);
}


//tested 27 nov 2020
string repeat(string str, int n)
{
  string repeat_str= "";
  for(int k=0; k<n; k++)
    repeat_str += str;

  return repeat_str;
}

void Base::show_masks()
{
  // if(prettyOutput)
  //   cout << FinePrint::greenText("[+]") << " Base " << length << " :" << endl;
  // else
   cout << "[+] Base " << length << " :" << endl;

  for(auto mask: masks)
  {
    cout << "\t" << mask << endl;
  }
}

Mask Base::get_mask(int k)
{
  if (k > 0 && k < masks.size())
    return baseMasks->at(k);
  else
    throw out_of_range();
}

// REWRITE (NOT ALL) THIS FUNCTION  - date Apr 14  2021
void permute_base(Base base, ofstream* output)
/*
 * This function compute all the permutations of base's masks without repetitions
 * and write all of them to a file.
 */
{
  vector<Mask> ;
  for(int k=0; k<base->getNumberMasks(); k++)
  {
    Mask kmask = base->getMask(k);
    bool repeatMask = false;
    //#pragma omp parallel for shared(repeatMask, kmask, base)
    for(int i=k+1; i<base->getNumberMasks(); i++)
    {
      if(repeatMask) continue;
      Mask imask = base->getMask(i);

      if(Mask::equalStruct(kmask, imask))
        repeatMask = true;
    }
    if(!repeatMask)
      baseMasks.push_back(kmask);
  }

#pragma omp parallel for shared(baseMasks)
  for(int k=0; k<baseMasks.size(); k++)
  {
    Mask mask = baseMasks.at(k);
    string maskSymbols = mask.getSymbols();
    string smask;
    do {
      smask = "";
      for(auto character: maskSymbols)
          smask += "?" + string(1,character);
      //#pragma omp critical
      output << smask << endl;
    } while ( std::next_permutation(maskSymbols.begin(),maskSymbols.end()) );

    smask = "";
    for(auto character: maskSymbols)
      smask += "?" + string(1,character);

    #pragma omp critical
    *outputPolicygen << smask << endl;
  }
}
