// next_permutation example
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <string>
#include "../../include/mask.hpp"

int main () {
    std::string ssmask = "?l?l?u?s?d";
    vector<Mask> baseMasks;
    Mask mmask(ssmask);
    baseMasks.push_back(mmask);
    for(auto mask: baseMasks)
    {
        string maskSymbols = mask.getSymbols();
        string smask;
        do {
            smask = "";
            for(auto character: maskSymbols)
                smask += "?" + std::string(1,character);
            std::cout << smask << endl;
        } while ( std::next_permutation(maskSymbols.begin(),maskSymbols.end()) );

        smask = "";
        for(auto character: maskSymbols)
            smask += "?" + std::string(1,character);
        std::cout << smask << endl;
    }
    return 0;
}