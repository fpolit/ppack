#ifndef __BASEMASK_H__
#define __BASEMASK_H__


#ifndef __INCLUDE_STD_STRING_H__
#define __INCLUDE_STD_STRING_H__
#include<string>
#endif //__INCLUDE_STD_STRING_H__

#ifndef __INCLUDE_STD_VECTOR_H__
#define __INCLUDE_STD_VECTOR_H__
#include<vector>
#endif //__INCLUDE_STD_VECTOR_H__

using namespace std;


#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "mask.hpp"
#endif //#define __INCLUDE_MASK_H__



#ifndef __INCLUDE_PPACK_H__
#define __INCLUDE_PPACK_H__
#include "../include/ppack.hpp"
#endif // __INCLUDE_PPACK_H__


class BaseMask
{
private:
  vector<Mask> base;
  unsigned int length;

public:
  //Base(poliStruct init);
  void maskStep();

  unsigned int getLength(){return length;}
  int numberMasks(){return base.size();}
};

#endif // __BASE_H__
