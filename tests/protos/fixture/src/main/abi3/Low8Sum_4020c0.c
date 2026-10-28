#include "types.h"
/* type macro (2026-10-25): the definition's return type is an object-like macro
   (CharaCollClampFloorCeilingMaybe_2364e0's `#define RT bool`); read as an unknown type it
   kept the definition out of game_protos.h and its callers' int views unchecked.  i686
   returns only AL: clang leaves the whole sum in EAX */
#define RT u8
RT Low8Sum_4020c0(s32 *p)
{
    return (u8)(p[0] + p[1]);
}
