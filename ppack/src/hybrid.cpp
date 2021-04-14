/*
 * Implementation of mask resolution for hybrid attacks - date Apr 14 2021
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#include "../include/hybrid.hpp"

Hybrid::Hybrid(Mask init_mask)
{
  word = "";
  mask = init_mask;
}

Hybrid::Hybrid(string init_word ,Mask init_mask)
{
  word = init_word;
  mask = init_mask;
}


void Hybrid::expand()
{
  string init_word = word;
  Mask init_mask = mask.split(1);
  string charsets;
  string mask_symbol = mask[0];
  Charsets charset;

  if (mask_symbol == "?l")
    charsets = charset.ascii_loweralpha;
  else if (mask_symbol == "?u")
    charsets = charset.ascii_upperalpha;
  else if (mask_symbol == "?d")
    charsets = charset.digits;
  else if (mask_symbol == "?s")
    charsets = charset.special;
  else //if (mask_symbol == "?a")
    charsets = charset.all;

  for (auto character: charsets)
    {
      init_word += character;
      branches.push_back(Hybrid(init_word, init_mask));
    }
}

void Hybrid::reset_branches(vector<Hybrid> sons_branches)
{
  branches = sons_branches;
}

bool Hybrid::has_empty_mask()
{
  if (mask == NONE_MASK)
    return true;
  return false;
}

bool Hybrid::is_final_expansion()
{
  for(Hybrid branch: branches)
    {
      if (!branch.has_empty_mask())
        return false;
    }
  return true;
}


void Hybrid::expandall()
{
  this->expand();
  bool full_expansion = false;
  vector<Hybrid> son_branches;
  vector<Hybrid> all_son_branches;
  do{
    all_son_branches.clear();
    for(Hybrid branch: branches)
      {
        branch.expand();
        son_branches = branch.get_branches();
        for (Hybrid son_branch: son_branches)
          all_son_branches.push_back(son_branch);
      }
    this->reset_branches(all_son_branches);
    full_expansion = this->is_final_expansion();

  }while (full_expansion);
}
