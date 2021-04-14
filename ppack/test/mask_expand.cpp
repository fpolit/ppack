#include "../include/hybrid.hpp"
#include <iostream>

using namespace std;

int main()
{
  Mask init_mask = Mask("?d?l?u");
  Hybrid root = Hybrid(init_mask);

  root.expandall();

  for(Hybrid branch: root.get_branches())
    {
      cout << "word: " << branch.get_word() << " , mask: " << branch.get_mask() << endl;
    }
}
