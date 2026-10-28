#include "types.h"
/* the decomp's int view of a u8 definition (CharaMoveCollideMaybe_234dc0 shape): ret-narrow
   once the definition's macro return type is resolved */
extern "C" {
s32 Low8Sum_4020c0(s32 *p);

s32 NarrowIntUser_4020e0(s32 *p)
{
    return Low8Sum_4020c0(p) != 0;
}
}
