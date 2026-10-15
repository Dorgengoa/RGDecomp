#include "types.h"

extern s32 VariantGetInt_15f780(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const u8 D_00495EA1;

s32 TexAnimeCfgAlphaBlendCmd_1621e0(s32 p0, s32 p1)
{
    s32 r0;

    if (p1 > 0) {
        r0 = VariantGetInt_15f780(p0);
        *(u8 *)&D_00495EA1 = r0;
    }
    return 1;
}
