#include "types.h"

extern void LightningMgrAddObjEmitter_2d6cb0(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004E6110[];

void LightningRequestOnObj_2d7de0(s32 p0, s32 p1)
{
    LightningMgrAddObjEmitter_2d6cb0(D_004E6110, p0, p1);
}
