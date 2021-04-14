/*
 * Statsgen - implementation of core functions
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef _CORE_STATSGEN_H
#define _CORE_STATSGEN_H

bool sfilter(Password passwd, sstruct pargs);
vector<Password> passwdBlock(ifstream *wordlist, int block,
                             sstruct pargs, unsigned long* totalPasswd);

statstruct coreStatsgen(sstruct pargs);
double formatPercent(double decimalPercent);
void writeStatsgen(statstruct stats, sstruct pargs);

#endif // _CORE_STATSGEN_H
