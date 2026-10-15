#include "types.h"

extern s32 VariantReadVec3_15f6c0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481270;

s32 MapCfgPartsPos_18bc90(s32 p0)
{
    s32 r0;

    r0 = VariantReadVec3_15f6c0(&D_00481270, p0);
    return 1;
}
