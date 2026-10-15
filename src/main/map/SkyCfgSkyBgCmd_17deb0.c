#include "types.h"

extern s32 SlotGetInt_15f720(s32);
extern s32 strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004811AC;

s32 SkyCfgSkyBgCmd_17deb0(s32 p0)
{
    s32 r0;
    s32 t0;
    s32 r1;

    r0 = SlotGetInt_15f720(p0);
    if (r0 != 0) {
        t0 = D_004811AC;
        r1 = strcpy((t0 + 0x224), r0);
    }
    return 1;
}
