#include "types.h"

extern void MapDataEnableStackPop_1e72a0(s32);
extern void MapDataHiddenStackPop_1e7270(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MapDataFlagsPop_1e7210(s32 p0)
{
    MapDataEnableStackPop_1e72a0(p0);
    MapDataHiddenStackPop_1e7270(p0);
}
