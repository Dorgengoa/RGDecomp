#include "types.h"

extern s32 GetMinimapSubGlobal_32c2c0(void);
extern s32 VariantGetInt_15f780(s32);
extern void MinimapSubSetCapacity_32aea0(s32, s32);
extern void MinimapSubAllocArray_32af20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MinimapScriptCmdAllocSub_32ae20(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = GetMinimapSubGlobal_32c2c0();
    if (r0 != 0) {
        r1 = VariantGetInt_15f780(p0);
        MinimapSubSetCapacity_32aea0(r0, r1);
        MinimapSubAllocArray_32af20(r0);
    }
    return 1;
}
