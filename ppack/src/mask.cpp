/*
 * Mask class implementation
 * Mask class reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */



#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
//#include <string>
#endif //__INCLUDE_MASK_H__





// character.hpp
string masksymbols = R"(ludsa)";

// characterSet map (SCS or ACS -> string values)

// string Values of Simple Charsets
map<SCS, string> scsMap = {
  {SCS::loweralpha, "loweralpha"},
  {SCS::upperalpha,"upperalpha"},
  {SCS::numeric,"numeric"},
  {SCS::special,"special"},
  {SCS::alpha,"alpha"},
  {SCS::mixalphaspecial,"mixalphaspecial"},
  {SCS::mixalphanum, "mixalphanum"},
  {SCS::mixspecialnum, "mixspecialnum"},
  {SCS::mixall, "mixall"},
  {SCS::none, "none"}
};


// string Values of advance Charsets
map<ACS, string> acsMap = {
  {ACS::alphaspecial, "alphaspecial"},
  {ACS::loweralphaspecial, "loweralphaspecial"},
  {ACS::upperalphaspecial, "upperalphaspecial"},
  {ACS::specialalpha, "specialalpha"},
  {ACS::specialloweralpha, "specialloweralpha"},
  {ACS::specialupperalpha, "specialupperalpha"},
  {ACS::alphanum, "alphanum"},
  {ACS::loweralphanum, "loweralphanum"},
  {ACS::upperalphanum, "upperalphanum"},
  {ACS::specialnum, "specialnum"},
  {ACS::numspecial, "numspecial"},
  {ACS::advnone, "none"}
};


/*
 * Mask exceptions
*/

InvalidMaskcharset::InvalidMaskcharset(string invalidMaskCharset)
{
  maskCharset = invalidMaskCharset;
}

const char * InvalidMaskcharset::what() const throw ()
{
  string warningMsg = "Invalid MaskCharset: " + maskCharset;
  return warningMsg.c_str();
}

InvalidMask::InvalidMask(string invalidMask)
{
  mask = invalidMask;
}

 const char * InvalidMask::what () const throw ()
 {
    string warningMsg = "Invalid Mask: " + mask;
    return warningMsg.c_str();
 }
// head of functions

// check methods
// bool ismask(string mask);
// bool checkLength(Mask mask, int minlength, int maxlength);
// bool checkSCS(Mask mask, vector<SCS> scs); //check if mask have one of the simple Charset of scs
// bool checkACS(Mask mask, vector<ACS> acs); //check if mask have one of the advance Charset of acs
// bool checkComplexity(Mask mask, int minCompexity, int maxComplexity);
// bool isMaskCharset(string maskCharset); // check if a symbols is a valid symbol mask

// get and set methods
//ACS Mask::getACS()

// modificator methods
//void Mask::realloc(string maskCharset); // add a mask symbol to a mask and update mstruct
//vector<Mask> Mask::permutations();
Mask reallocMask(Mask mask, string maskCharset) // add maskCharset to mask
{
  Mask rmask = mask;
  rmask.realloc(maskCharset);
  return rmask;
}


// friend methods
//Mask Mask::analysis(string mask);
//SCS scsParser(maskStruct mstruct);

Mask::Mask()
  :string("")
{
  // mstruct is initilizated to zeros by default
  charset = SCS::none;
  complexity=0;
  advanceCharset = ACS::advnone; //init advanceCharset with none, use only the set method to get acs
}


Mask::Mask(string mask)
  :string("") // NOTA: EL CONTRUCTOR DE LA CLASE PADRE (string) DEBE IR AQUI NO EN EL CUERPO SINO NO FUNCIONA.
{
  try{
    if(!ismask(mask))
      throw InvalidMask(mask);

    // mask analysis
    for(int i=1; i<(int)mask.size(); i+=2)
      {
        switch(mask[i])
          {
          case 'l':
            this->realloc("?l");
            break;
          case 'd':
            this->realloc("?d");
            break;
          case 'u':
            this->realloc("?u");
            break;
          case 's':
            this->realloc("?s");
            break;
          }
      }

    charset = scsParser(mstruct);
    complexity = 0; // implement a function to compute mask complexity
    advanceCharset = ACS::advnone; //init advanceCharset with none, use only the set method to get acs

  }
  catch(invalid_argument& error)
    {
      cerr << error.what() << endl;
    }
}




// check friend methods
// Tested with omp support
bool Mask::ismask(string mask)
{
  bool master_ismask = true;
#pragma omp parallel for shared(master_ismask)
  for(int k=1; k<(int)mask.size(); k+=2)
    {
      // if the string mask  isn't a mask, then only pass.
      if(!master_ismask)  continue;

      if(masksymbols.find(mask[k], 0) == string::npos)
        {
          #pragma omp critical
          master_ismask = false;
        }
    }
  return master_ismask;
}


bool Mask::checkLength(Mask mask, int minlength, int maxlength)
{
  int maskLength = mask.length();
  if(maxlength != -1)
  {
    if(maskLength >= minlength && maskLength <= maxlength)
    return true;
  }  
  else
  {
    if(maskLength >= minlength)
    return true;
  }
  return false;
}


// bool checkSCS(Mask mask, vector<SCS> charsets)
// {

//   // CHECK BUG
//   if(find(charsets.begin(), charsets.end(), mask.getSCS()) != charsets.end())
//      return true;
//   return false;
// }


// bool checkACS(Mask mask, vector<ACS> charsets)
// {

//   // CHECK BUG
//   if(find(charsets.begin(), charsets.end(), mask.getACS()) != charsets.end())
//      return true;
//   return false;
// }


bool Mask::checkComplexity(Mask mask, int mincomplexity, int maxcomplexity)
{
  int complexity = mask.getComplexity();
  if(maxcomplexity != -1)
  {
    if(complexity >= mincomplexity && complexity <= maxcomplexity)
    return true;
  }  
  else
  {
    if(complexity >= mincomplexity)
    return true;
  }
  return false;
}



bool isMaskCharset(string maskCharset) // check if a symbols is a valid symbol mask
{
  if(maskCharset.size() == 2)
    {
      if(masksymbols.find(maskCharset[1], 0) != string::npos)
        return true;
    }
  return false;

}


// get and set methods
string Mask::getValueSCS()
{
  return scsMap[charset];
}
string Mask::getValueACS()
{
  ACS acs = this->getACS();
  return acsMap[acs];
}

string Mask::getSymbols()
{
  string symbols = "";
  for(int k =1; k<this->size(); k+=2)
    symbols += this->at(k);

  return symbols;
}


ACS Mask::getACS()
{
  if(advanceCharset != ACS::advnone)
    return advanceCharset;
  else
    {
      // compute the ASC and the return advanceCharset
      return advanceCharset;
    }
}

void Mask::realloc(string maskCharset)
{
  try{
    if(!isMaskCharset(maskCharset))
      throw InvalidMaskcharset(maskCharset);

    if(maskCharset == "?l")
      mstruct.lowercase += 1;
    else if(maskCharset == "?u")
      mstruct.uppercase += 1;
    else if(maskCharset == "?d")
      mstruct.digit += 1;
    else // special maskCharset
      mstruct.special += 1;

    // finally add the maskChatset to the mask
    *this += maskCharset;
  }
  catch(exception& error)
    {
      cerr << error.what() << endl;
    }

}

// vector<Mask> Mask::permutations()
// {
//   // perform all the permutation of the mask
//   cout << "No forget implement permutation method(Mask Class)." << endl;
// }

Mask Mask::analysis(string mask)
{
  Mask gmask(""); // generate mask (empty)

  try{
    if(!ismask(mask))
      throw InvalidMask(mask);

    //#pragma omp parallel for shared(mask)
    for(int i=1; i<(int)mask.size(); i+=2)
      {
        switch(mask[i])
          {
          case 'l':
            gmask.realloc("?l");
            break;
          case 'd':
            gmask.realloc("?d");
            break;
          case 'u':
            gmask.realloc("?u");
            break;
          case 's':
            gmask.realloc("?s");
            break;
          }
      }

    maskStruct mstruct = gmask.getStruct();
    gmask.setSCS(scsParser(mstruct));

    return gmask;
  }
    catch(exception& error)
      {
        cerr << error.what() << endl;
        return Mask("");
      }
}



SCS Mask::scsParser(maskStruct mstruct)
{
    // parse a maskStruct to determine the scs of the mask

    if(mstruct.lowercase &&
        !(mstruct.digit || mstruct.uppercase || mstruct.special))
        return SCS::loweralpha;
    // corregir return
    else if(mstruct.uppercase &&
        !(mstruct.lowercase || mstruct.digit || mstruct.special))
        return SCS::upperalpha;

    else if(mstruct.digit &&
        !(mstruct.lowercase || mstruct.uppercase || mstruct.special))
        return SCS::numeric;

    else if(mstruct.special &&
        !(mstruct.lowercase || mstruct.uppercase || mstruct.digit))
        return SCS::special;

    else if((mstruct.uppercase && mstruct.lowercase) &&
        !(mstruct.special || mstruct.digit))
        return SCS::alpha;

    else if((mstruct.special && mstruct.uppercase && mstruct.lowercase) &&
        !(mstruct.digit))
        return SCS::mixalphaspecial;

    else if((mstruct.digit && mstruct.uppercase && mstruct.lowercase) &&
        !(mstruct.special))
        return SCS::mixalphanum;

    else if((mstruct.digit && mstruct.special) &&
        !(mstruct.uppercase || mstruct.lowercase))
        return SCS::mixspecialnum;

    else if(mstruct.special && mstruct.lowercase && mstruct.uppercase && mstruct.digit)
        return SCS::mixall;

    else
        return SCS::none;
}


string Mask::scstoString(SCS simpleCharset) // return the string value of the SCS simpleCharset
{
  return scsMap[simpleCharset];
}

string Mask::acstoString(ACS advanceCharset) // return the string value of the ACS advanceCharset
{
  return acsMap[advanceCharset];
}

bool Mask::equalStruct(Mask kmask, Mask imask)
{
  maskStruct kmstruct = kmask.getStruct();
  maskStruct imstruct = imask.getStruct();
  if( kmstruct.lowercase == imstruct.lowercase &&
      kmstruct.uppercase == imstruct.uppercase &&
      kmstruct.digit == imstruct.digit &&
      kmstruct.special == imstruct.special)
    return true;
  return false;
}

SCS Mask::checkSCS(string pscs)
{
  for(auto [scs, valueSCS]: scsMap)
  {
    if(pscs == valueSCS)
      return scs;
  }
  return SCS::none;
}

ACS Mask::checkACS(string pacs)
{
  for(auto [acs, valueACS]: acsMap)
  {
    if(pacs == valueACS)
      return acs;
  }
  return ACS::advnone;
}