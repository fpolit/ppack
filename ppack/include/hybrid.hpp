/*
 * Definition of mask resolution for hybrid attacks - date Apr 14 2021
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#include <string>
#include <vector>

using namespace std;

#ifndef _MASK_H
#include "mask.hpp"
#endif

#ifndef _MASK_EXCEPT_H
#include "exceptions/mask.hpp"
#endif

#ifndef _CHARSET_H
#include "charset.hpp"
#endif

#ifndef _HYBRID_H
#define _HYBRID_H

class Hybrid
{
private:
  string word;
  Mask mask;
  vector<Hybrid> branches;
  //vector<Hybrid> leafs;

public:
  Hybrid(Mask init_mask);
  Hybrid(string init_word, Mask init_mask);

  Mask get_mask(){return mask;}
  string get_word(){return word;}
  vector<Hybrid> get_branches(){return branches;}
  void reset_branches(vector<Hybrid> sons_branches);
  bool is_final_expansion();
  bool has_empty_mask();
  // expand init mask and generate leafs
  void expand();
  void expandall();
};

#endif //_HYBRID_H
