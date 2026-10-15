#include "types.h"

extern s32 VariantReadVec3_15f6c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004812F4;

s32 MapSceneCfgCharaPos_192ae0(s32 p0)
{
    s32 r;

    r = VariantReadVec3_15f6c0((D_004812F4 + 0x170), p0);
    return 1;
}
