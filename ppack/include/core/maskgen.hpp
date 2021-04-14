/*
 * Maskgen - implementation of core functions
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef _CORE_MASKGEN_H
#define _CORE_MASKGEN_H

bool checkOccurrence(unsigned int maskOccurrence, unsigned int minoccurence, int maxoccurence);
bool mFilter(Mask mask, unsigned int occurrence, mstruct pargs);
void coreMaskgen(ofstream *maskgenOutput, vector<vector<string>> statsgenResults, mstruct pargs);

#endif // _CORE_MASKGEN_H
