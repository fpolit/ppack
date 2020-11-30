
/*
 * Logos class definition - Sep 27, 2020 
 *
 * 
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */

#ifndef __LOGOS_H__
#define __LOGOS_H__

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include <vector>
#endif //__INCLUDE_STD_VECTOR_H__

#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

#ifndef __INCLUDE_STD_RANDOM_H__
#define __INCLUDE_STD_RANDOM_H__
#include <random>
#endif //__INCLUDE_STD_RANDOM_H__


#ifndef __INCLUDE_STD_CTIME_H__
#define __INCLUDE_STD_CTIME_H__
#include <ctime>
#endif //__INCLUDE_STD_CTIME_H__

#include <iostream>

using namespace std;

class Logo
{
protected:
	vector<string> rawLogos;

public:
	Logo();
	static string randomLogo();
};
#endif /* __LOGOS_H__ */