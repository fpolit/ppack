/*
 * Mask class implementation
 * Mask class reimplemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#include "../include/mask.hpp"


Mask::Mask()
  :string("")
{
  // mstruct is initilizated to zeros by default
  charset = SCS::none;
  complexity=0;
  adv_charset = ACS::advnone; //init advanceCharset with none, use only the set method to get acs
}


Mask::Mask(string mask)
  :string("") // NOTA: EL CONTRUCTOR DE LA CLASE PADRE (string) DEBE IR AQUI NO EN EL CUERPO SINO NO FUNCIONA.
{
  try{
    if(!Mask::ismask(mask))
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

    charset = scs_parser(mstruct);
    complexity = 0; // implement a function to compute mask complexity
    adv_charset = ACS::advnone; //init advanceCharset with none, use only the set method to get acs

  }
  catch(invalid_argument& error)
    {
      cerr << error.what() << endl;
    }
}


// check static methods
// Tested with omp support
bool Mask::ismask(string mask)
{
  bool master_ismask = true;
  //#pragma omp parallel for shared(master_ismask)
  Charsets charsets;
  for(int k=1; k<(int)mask.size(); k+=2)
    {
      // if the string mask  isn't a mask, then only pass.
      if(!master_ismask)  continue;

      if(charsets.masksymbols.find(mask[k], 0) == string::npos)
        {
          //#pragma omp critical
          master_ismask = false;
        }
    }
  return master_ismask;
}


bool Mask::check_length(Mask mask, int minlength, int maxlength)
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


// bool Mask::check_scs(Mask mask, vector<SCS> scs)
// {

//   // CHECK BUG
//   if(find(scs.begin(), scs.end(), mask.get_scs()) != scs.end())
//      return true;
//   return false;
// }


// bool Mask::check_acs(Mask mask, vector<ACS> acs)
// {

//   // CHECK BUG
//   if(find(acs.begin(), acs.end(), mask.get_acs()) != acs.end())
//      return true;
//   return false;
// }


bool Mask::check_complexity(Mask mask, int mincomplexity, int maxcomplexity)
{
  int complexity = mask.get_complexity();
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



bool Mask::is_mask_charset(string maskCharset) // check if a symbols is a valid symbol mask
{
  Charsets charsets;
  if(maskCharset.size() == 2)
    {
      if(charsets.masksymbols.find(maskCharset[1], 0) != string::npos)
        return true;
    }
  return false;

}


// // get and set methods
// string Mask::getValueSCS()
// {
//   return scsMap[charset];
// }
// string Mask::getValueACS()
// {
//   ACS acs = this->getACS();
//   return acsMap[acs];
// }

string Mask::symbols()
{
  string symbols = "";
  for(int k =1; k<this->size(); k+=2)
    symbols += this->at(k);

  return symbols;
}

// ACS Mask::getACS()
// {
//   if(advanceCharset != ACS::advnone)
//     return advanceCharset;
//   else
//     {
//       // (IMPLEMENT) compute the ASC and the return advanceCharset
//       return advanceCharset;
//     }
// }

// modificator methods
void Mask::realloc(string mask_charset)
{
  try{
    if(! Mask::is_mask_charset(mask_charset))
      throw InvalidMaskCharset(mask_charset);

    if(mask_charset == "?l")
      mstruct.lowercase += 1;
    else if(mask_charset == "?u")
      mstruct.uppercase += 1;
    else if(mask_charset == "?d")
      mstruct.digit += 1;
    else // special maskCharset
      mstruct.special += 1;

    // finally add the maskChatset to the mask
    *this += mask_charset;
  }
  catch(exception& error)
    {
      cerr << error.what() << endl;
    }

}

Mask realloc_mask(Mask mask, string mask_charset) // add maskCharset to mask
{
  Mask rmask = mask;
  rmask.realloc(mask_charset);
  return rmask;
}

// vector<Mask> Mask::permutations()
// {
//   // perform all the permutation of the mask
//   cout << "No forget implement permutation method(Mask Class)." << endl;
// }


// parser functions
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

    maskStruct mstruct = gmask.get_mask_struct();
    gmask.set_scs(scs_parser(mstruct));

    return gmask;
  }
    catch(exception& error)
      {
        cerr << error.what() << endl;
        return Mask("");
      }
}



SCS Mask::scs_parser(maskStruct mstruct)
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
        return SCS::mix_alpha_special;

    else if((mstruct.digit && mstruct.uppercase && mstruct.lowercase) &&
        !(mstruct.special))
        return SCS::mix_alpha_num;

    else if((mstruct.digit && mstruct.special) &&
        !(mstruct.uppercase || mstruct.lowercase))
        return SCS::mix_special_num;

    else if(mstruct.special && mstruct.lowercase && mstruct.uppercase && mstruct.digit)
        return SCS::mix_all;

    else
        return SCS::none;
}


string Mask::scs2string(SCS simpleCharset) // return the string value of the SCS simpleCharset
{
  return scs_map[simpleCharset];
}

string Mask::acs2string(ACS advanceCharset) // return the string value of the ACS advanceCharset
{
  return acs_map[advanceCharset];
}

bool Mask::equal_struct(Mask kmask, Mask imask)
{
  maskStruct kmstruct = kmask.get_mask_struct();
  maskStruct imstruct = imask.get_mask_struct();
  if( kmstruct.lowercase == imstruct.lowercase &&
      kmstruct.uppercase == imstruct.uppercase &&
      kmstruct.digit == imstruct.digit &&
      kmstruct.special == imstruct.special)
    return true;
  return false;
}

SCS Mask::check_scs(string pscs)
{
  for(auto [scs, value_scs]: scs_map)
  {
    if(pscs == value_scs)
      return scs;
  }
  return SCS::none;
}

ACS Mask::check_acs(string pacs)
{
  for(auto [acs, value_acs]: acs_map)
  {
    if(pacs == value_acs)
      return acs;
  }
  return ACS::advnone;
}


string Mask::operator[](int index)
{
  if(index < 0 || index > this->length())
    return "?" + this[2*index + 1];
  else
    {
      string warning = "Invalid index: " + index;
      throw out_of_range(warning.c_str());
    }
}

bool Mask::operator==(const Mask other)
{
  //maskStruct ms = other.get_mask_struct();
  if (Mask::equal_struct(*this, other) &&
      this->compare(other) == 0)
    return true;
  return false;
}

Mask Mask::split(int index)
{
  if(index < 0 || index > this->length())
    {
      Mask split_mask = Mask();
      for(int i=index; i<this->length(); i++)
        split_mask.realloc(this[i]);

      return split_mask;
    }
  else
    {
      string warning = "Invalid index: " + index;
      throw out_of_range(warning.c_str());
    }
}
