/*
 * Mask exceptions classes definition
 * Mask exceptions  class implemented 23 nov 20202
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


#ifndef __INCLUDE_STD_IOSTREAM_H__
#define __INCLUDE_STD_IOSTREAM_H__
#include <iostream>
#endif //__INCLUDE_STD_IOSTREAM_H__

#ifndef __INCLUDE_STD_EXCEPTION_H__
#define __INCLUDE_STD_EXCEPTION_H__
#include <exception>
#endif //__INCLUDE_STD_EXCEPTION_H__


struct invalid_maskcharset : public std::exception
{
  const char * what () const throw ()
  {
    return "Invalid mask charset.";
  }
}invalid_maskcharset;



struct invalid_mask : public std::exception
{
  const char * what () const throw ()
  {
    return "Invalid mask.";
  }
}invalid_mask;
