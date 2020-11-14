#ifndef __INCLUDE_BASEMASK_H__
#define __INCLUDE_BASEMASK_H__
#include "../include/base.hpp"
#endif //__INCLUDE_BASE_H__

#ifndef __INCLUDE_MASK_H__
#define __INCLUDE_MASK_H__
#include "../include/mask.hpp"
#endif //#define __INCLUDE_MASK_H__


BaseMask::BaseMask(Mask init_base)
{
  // note: implement a exception and rewrite this part of inizialization
  if(ismask(init_base))
    {
      base.push_back(init_base);
      length = 1;
    }
}

// void BaseMask::maskStep()
// {
//   for(Mask mask : base)
//     {
//       if(mask.mstruct.lowercase <)
//     }
// }
