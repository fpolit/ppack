
/*
 * ppack logos
 *
 * implementation - Sep 27, 2020
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef _LOGOS_H
#define _LOGOS_H

#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <iostream>

using namespace std;


namespace ppack{

  class Logo
  {
  protected:
	vector<string> raw_logos;

  public:
	Logo();
	static string random();
  };
}

#endif /* _LOGOS_H */
